![volume](/devOps/kubernetes/image/Volume.png)

## emptyDir

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

## hostPath

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

### Type

- DirectoryOrCreate : 실제 경로가 없다면 생성
- Directory : 실제 경로가 있어야지 가능
- FileOrCreate : 실제 경로에 파일이 없다면 생성
- File : 실제 경로에 파일이 있어야 가능

## PVC / PV (Persistent Volume Claim)

하드같이 데이터를 영속성을 가진 상태로 사용하고 싶을때 사용할 수있는데 PV는 인프라를 관리하는 Admin이 설정하며, PVC는 이 volume를 사용하기 위해 사용되는 목적으로 사용할 수 있다.

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
