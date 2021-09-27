![volume2](/devOps/kubernetes/image/volume2.png)

데이터를 안정적으로 관리하기 위해 사용되어 cluster와 분리되어 존재

관리자가 저장용량/access mode를 설정해 pv를 만들고 사용자가 pvc를 만들면 k8s가 적절한 pv를 연결해주며 access mode에는 3가지가 존재한다. 이런 연결방식은 volume이 필요할때마다 pv를 만들어주어야 하고 이를 연결하기 위해 storage/access mode를 맞추주어야 하는데 이를 해결하기 위해 dynamic provisioning이 존재한다.


## 1. 명령어
```sh
# namespace내의 모든 objects들 조회
kubectl get all -n storagesos-operator

# Force Deletion
kubectl delete persistentvolumeclaims pvc-fast1 --namespace=default --grace-period 0 --force
kubectl delete persistentvolume pvc-b53fd802-3919-4fb0-8c1f-02221a3e4bc0 --grace-period 0 --force

# StorageClass 확인
kubectl get storageclasses.storage.k8s.io
```

## volume mount

![volume](/devOps/kubernetes/image/Volume.png)

### 1) emptyDir

컨테이너들끼리 데이터를 공유하기 위해 볼륨을 사용하는 것으로 이 볼륨이 처음 생성될때는 항상 비어있기 때문에 empty라 불리는 것

볼륨은 파드안에 생성이 되는 것이기 때문에 파드가 삭제가 된다면 같이 삭제가 되기 때문에 일시적인 데이터를 저장할때 이용하는 것이 좋다.

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-volume-1
spec:
  containers:
    - name: container1
      image: tmkube/init
      volumeMounts:
        - name: empty-dir
          mountPath: /mount1
    - name: container2
      image: tmkube/init
      volumeMounts:
        - name: empty-dir
          mountPath: /mount2
  volumes:
    - name: empty-dir
      emptyDir: {}
```

### 2) hostPath

파드들이 들어있는 노드의 path를 볼륨으로써 사용하는 경우가 hostPath이며, 파드들이 볼륨을 마운트하는 것이기 때문에 파드가 죽어도 볼륨이 삭제되지는 않는다. 하지만 파드가 죽고 재생성되는 순간에 이전에 생성되었던 노드에 생성되리라는 보장이 없는데 이렇게 다른 노드에 파드가 재생성되게 되면 이전에 마운트했던 볼륨에 접근할 수 없게 된다.

파드가 생성될때마다 노드내에 볼륨을 새로 마운트해줌으로써 해결할 수 있지만 k8s가 자동적으로 지원해주는 기능이아니라 운영자가 개별적으로 설정해주어야 하는 부분이라 실수의 여지가 존재한다.

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-volume-2
spec:
  cointainers:
    - name: cotainer
      image: tmkube/init
      volumeMounts:
        - name: host-path
          mountPath: /mount1
  volumes:
    - name: host-path
      host-path:
        path: /node-v
        type: Diretory
```

이때 host-path의 `path`는 파드가 생성되기 전에 노드에 생성이 되어있어야 마운트가 가능하다.

#### Type

- DirectoryOrCreate : 실제 경로가 없다면 생성
- Directory : 실제 경로가 있어야지 가능
- FileOrCreate : 실제 경로에 파일이 없다면 생성
- File : 실제 경로에 파일이 있어야 가능

### 3) PVC / PV (Persistent Volume Claim)

하드같이 데이터를 영속성을 가진 상태로 사용하고 싶을때 사용할 수있는데 PV는 인프라를 관리하는 Admin이 설정하며, PVC는 이 volume를 사용하기 위해 사용되는 목적으로 사용할 수 있다.

```yml
#PV
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-03
spec:
  capacity:
    storage: 2G
  accessModes:
  - ReadWriteOnce
  local:
    path: /node-v
  nodeAffinity:
    required:
      nodeSelectorTerms:
      - matchExpressions:
        - {key: kubernetes.io/hostname, operator: In, values: [k8s-node1]}
```
```yml
#PV
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: pvc-01
spec:
  accessModes:
  - ReadWriteOnce
  resources:
    requests:
      storage: 1G
  storageClassName: ""
```
```yml
#Pod
apiVersion: v1
kind: Pod
metadata:
  name: pod-volume-3
spec:
  containers:
  - name: container
    image: kubetm/init
    volumeMounts:
    - name: pvc-pv
      mountPath: /mount3
  volumes:
  - name : pvc-pv
    persistentVolumeClaim:
      claimName: pvc-01
```

#### Pv - PVC label로 연결
```yml
#PV
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-04
  labels:
    pv: pv-04
spec:
  capacity:
    storage: 2G
  accessModes:
  - ReadWriteOnce
  local:
    path: /node-v
  nodeAffinity:
    required:
      nodeSelectorTerms:
      - matchExpressions:
        - {key: kubernetes.io/hostname, operator: In, values: [k8s-node1]}
```
```yml
#PV
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: pvc-04
spec:
  accessModes:
  - ReadWriteOnce
  resources:
    requests:
      storage: 2G
  storageClassName: ""
  selector:
    matchLabels:
      pv: pv-04
```

## Dynamic Provisioning
![dynamicProvisioning](/devOps/kubernetes/image/dynamicProvisioning.png)
사용자가 pvc를 만들면 알아서 pv를 만들어주고 volume을 연결해주는 기능이며 모든 pv에는 각각의 `상태`가 존재하고 pv를 삭제할때 `정책`의 요소도 존재한다.


### 1) Dynamic Provisioning
![dp](/devOps/kubernetes/image/dp.png)

위에서 local PV를 이용해 PVC를 만들때 ClassName을 `""`로 주었는데 이처럼 ""는 local, 특정 solution/cloud를 이용한 PV를 사용할때는 해당 storageClass를 주어지면 해당 volume이 동적으로 만들어지며 default Storage를 생성해두었다면 className을 아무것도 주어지지 않으면 defalut class를 이용해 생성이된다.

```yml
# Storage class
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: default
  annotations:
    # Default StorageClass로 선택 
    storageclass.kubernetes.io/is-default-class: "true" 
# 동적으로 PV생성시 PersistentVolumeReclaimPolicy 선택 (Default:Delete)
reclaimPolicy: Retain, Delete, Recycle
provisioner: kubernetes.io/storageos
# provisioner 종류에 따라 parameters의 하위 내용 다름 
parameters:     
```
```yml
#PV
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-hostpath1
spec:
  capacity:
    storage: 1G
  accessModes:
  - ReadWriteOnce
  hostPath:
    path: /mnt/hostpath
    type: DirectoryOrCreate
```
```yml
#PVC (local)
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: pvc-hostpath1
spec:
  accessModes:
  - ReadWriteOnce
  resources:
    requests:
      storage: 1G
  storageClassName: ""
```
```yml
#PVC (storage Class)
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: pvc-fast1
spec:
  accessModes:
  - ReadWriteOnce
  resources:
    requests:
      storage: 1G
  storageClassName: "fast"
```
```yml
#PVC (default)
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: pvc-default1
spec:
  accessModes:
  - ReadWriteOnce
  resources:
    requests:
      storage: 2G
```
### 2) Status / ReclaimPolicy
![status-reclaimPolicy](/devOps/kubernetes/image/status-reclaim.png)

#### Status
1. available : 처음 pv가 생성되어있을때의 상태
1. Bound : PVC와 연결되어 있는 상태로 PV를 직접만드는 경우에는 volume에 실제 데이터가 만들어진 상태는 아니고 pod가 pvc를 사용해서 고정이 될때 실제 데이터가 만들어진다.

  pod를 삭제한다고 해서  pvc가 삭제되는 것이 아니기 때문에 상태가 변하지 않는다.
1. Released : pvc가 삭제되어 pv와 연결이 끊어진 상태
1. Failed : 위 상태 전환간 문제가 발생한 상태

#### Reclaim Policy
1. Retain : 이 정책이 default로 pvc가 삭제되었을때 pv가 released로 변환되며 실제 데이터는 유지 되지만 이 pv를 다른 pvc에 연결할 수 없어 수동으로 pv를 삭제해주어야 한다.
1. Delete : pvc를 삭제하면 같이 pv가 삭제되어, storageClass를 사용시 default 값이다.
1. Recycle : 현재는 deprecated된 정책으로 데이터는 삭제되지만 pv는 재사용이 가능한 정책이다.

```yml
#Recycle
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-recycle1
spec:
  persistentVolumeReclaimPolicy: Recycle
  capacity:
    storage: 3G
  accessModes:
  - ReadWriteOnce
  hostPath:
    path: /tmp/recycle
    type: DirectoryOrCreate
```
Recycle 정책은 /tmp/로 시작하는 path에서만 가능하다.

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
