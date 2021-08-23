## 명령어

### 1. Create

```sh
# 파일이 있을 경우
kubectl create -f ./pod.yaml

# 내용과 함께 바로 작성
kubectl create -f - <<END
apiVersion: v1
kind: Pod
metadata:
  name: pod1
spec:
  containers:
  - name: container
    image: kubetm/init
END
```

기존에 같은 이름의 Pod가 존재하면 생성이 안된다.

### 2. Apply

```sh
kubectl apply -f ./pod.yaml
```

기존에 같은 이름의 Pod가 존재하면 내용이 override된다.

### 3. Get

```sh
# 기본 Pod 리스트 조회 (Namepsace 포함)
kubectl get pods -n defalut

# 좀더 많은 내용 출력
kubectl get pods -o wide

# Pod 이름 지정
kubectl get pod pod1

# Json 형태로 출력
kubectl get pod pod1 -o json
```

### 4. Describe

```sh
# 상세 출력
kubectl describe pod pod1
```

### 5. Delete

```sh
# 파일이 있을 경우 생성한 방법 그대로 삭제
kubectl delete -f ./pod.yaml

# 내용과 함께 바로 작성한 경우 생성한 방법 그대로 삭제
kubectl delete -f - <<END
apiVersion: v1
kind: Pod
metadata:
  name: pod1
spec:
  containers:
  - name: container
    image: kubetm/init
END

# Pod 이름 지정
kubectl delete pod pod1
```

### 6. Exec

```sh
# Pod이름이 pod1인 Container로 들어가기 (나올땐 exit)
kubectl exec pod1 -it /bin/bash

# Container가 두개 이상 있을때 Container이름이 con1인 Container로 들어가기
kubectl exec pod1 -c con1 -it /bin/bash
```

<br><br>

## 내부 설정

![pod](/devOps/kubernetes/image/pod.PNG)

### 1. 컨테이너

파드 내에 여러개의 컨테이너가 존재할 수 있으며 한 파드는 로컬과 같은 개념으로 서로다른 컨테이너끼리 포트가 중복될 수 없으며 파드가 생성될때 고유의 ip주소가 할당된다. 해당 ip주소는 클러스터내에서만 이용하여 파드에 접근할 수 있으며 외부에서는 접근 할 수 없다. 그리고 파드에 문제가 생긴다면 시스템이 파드를 삭제하고 재생성하게 되는데 이 ip는 재할당되므로 휘발성의 주소이다.

```yml
apiVersion: v1
kind: Pod
metadata:
    name: pod-1
spec:
    conatiners:
    - name: container1
       image: tmkube/p8000
       ports:
       - containerPort: 8000
    -name: container2
       image: tmkube/p8080
       ports:
       - cotainerPort: 8080
```

### 2. 라벨

각각의 파드별로 라벨을 여러개 달 수 있어 사용목적에 따라 파드를 분류할 수 있어 서비스를 이용해서 원하는 파드를 선택해서 사용할 수 있다.

```yml
apiVersion: v1
kind: Service
metadata:
  name: svc-1
spec:
  selector:
    type: web
  ports:
    - port: 8080
```

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-2
  lavels:
    type: web
    lo: dev
spec:
  containers:
    - name: container
  image: tmkube/init
```

### 3. 노드 스케줄

파드는 여러노드들 중에 한 노드에 올라가야되기 때문에 스케줄하는 방법이 두가지 존재한다.

#### 직접 선택

파드에 라벨을 단 것처럼 노드에 라벨을 만들어 직접 선택할 수 있다.

```yml
apiVersion: v1
kind: Pod
metadata:
    name: pod-3
spec:
    nodeSelector:
        hostname: node1
    containers:
        - name: container
        image: tmkube/init
```

#### 쿠버네티스가 판단하여 스케줄러가 선택

파드의 사용메모리량을 명시해주게 되는데 스케줄러가 판단하여 적절한 노드를 선택한다.

```yml
apiVersion: v1
kind: Pod
metadata:
    name: pod-4
spec:
    containers:
        - name: container
        image: tmkube/init
        resources:
            request:
                memory: 2Gi
            limits:
                memory: 3Gi
```

request는 해당 메모리를 요구한다는 의미이고 limits는 최대 사용량이며, 메모리의 limit을 초과시에는 파드를 바로 종료시키게 되고 cpu의 limit을 초과하게 되면 request로 낮추고 종료되지 않는다.

`메모리는 제한량을 초과하게 되면 다른 프로세스들의 메모리를 침범하게 되어 다른 프로그램에도 악영향을 미칠 수 있기 때문에 종료시키게 된다.`

<br>

## Node Schedule 방법

![nodeSchedule](/devOps/kubernetes/image/nodeSchedule.png)

```sh
kubectl label nodes k8s-node1 kr=az-1   #노드 라벨 추가
kubectl label nodes k8s-node2 us=az-1   #노드 라벨 추가

# Node에 라벨 삭제
kubectl label nodes k8s-node1 kr-  #노드에 라벨 삭제 (key값만 필요)
```

### 1. 노드 선택

#### NodeName

내가 원하는 노드를 선택하고 싶을때 스케줄러에 상관없이 명시적으로 노드를 선택할 수 있다는 특징이 있지만 실제 상용환경에서는 노드의 추가/삭제 과정중에서 노드의 이름이 변경될 수 있어 잘 사용되지는 않는다.

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: node-name
spec:
  nodeName: k8s-node1
  containers:
    - name: container
      image: kubetm/app
```

#### NodeSelector

파드에 key/value로 라벨을 달면 해당 라벨과 매칭되는 노드중에서 스케줄러에 의해 자원이 많은 노드로 파드가 할당된다. 라벨이 딱 매칭되는 노드에만 할당이 되기 때문에 매칭되는 경우가 없다면 할당이 이루어지지 않는다.

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: node-selector
spec:
  nodeSelector: key1:value1
  containers:
    - name: container
      image: kubetm/app
```

#### NodeAffinity

![nodeAffinity](/devOps/kubernetes/image/nodeAffinity.png)

파드에 key만을 가지고도 매칭되는 노드와 연결이 되며 매칭되는 노드가 존재하지 않더라도 스케줄러가 판단해서 자원이 많은 노드에 할당이되도록 옵션을 줄 수 있다.

matchExpressions를 이용하여 스케줄러가 노드와 파드를 연결해주게 된다. operator로 Gt와 Lt가 추가되고 `required/preferred`옵션을 통해서 노드에 없는 키를 가지고 있어도 할당되돋록 해줄 수 있다.

- required : key가 매칭되어야만 함

  ```yaml
  apiVersion: v1
  kind: Pod
  metadata:
   name: pod-required
  spec:
  affinity:
    nodeAffinity:
     requiredDuringSchedulingIgnoredDuringExecution:
      nodeSelectorTerms:
      - matchExpressions:
        - {key: ch, operator: Exists}
   containers:
   - name: container
     image: kubetm/app
   terminationGracePeriodSeconds: 0
  ```

- preferred : key가 매칭되지 않아도 스케줄러에 의해 할당이 가능

  - weight : 특정 라벨에 대한 가중치를 줌으로써 단순히 자원을 보고만 할당되는 것이 아닌 가중치를 합산해서 할당하기 위한 속성값

  ```yaml
  apiVersion: v1
    kind: Pod
    metadata:
     name: pod-preferred
    spec:
     affinity:
      nodeAffinity:
       preferredDuringSchedulingIgnoredDuringExecution:
        - weight: 1
          preference:
           matchExpressions:
           - {key: ch, operator: Exists}
     containers:
     - name: container
       image: kubetm/app
     terminationGracePeriodSeconds: 0
  ```

### 2. Pod간 집중 / 분산

#### Pod Affinity

![podAffinity](/devOps/kubernetes/image/podAffinity.png)

여러 파드들을 한 노드에 집중하여 할당

Web파드와 Server파드를 같은 PV(HostPath)를 사용해야 하는 경우에 같은 노드에 할당되도록 하려고 할때 파드의 타입을 동일하게 함으로써 같은 노드에 할당해주도록 해주는 기능

pod Affinity라는 옵션의 matchExpressions로 노드내의 파드라벨을 확인하고 topologyKey 옵션을 통해서 노드의 라벨의 조건을 줄 수 있다. 또한, Node Affinity와 마찬가지로 required/preferred옵션을 줄 수도 있다.

```yaml
# master pod
apiVersion: v1
kind: Pod
metadata:
 name: web1
 labels:
  type: web1
spec:
 nodeSelector:
  a-team: '1'
 containers:
 - name: container
   image: kubetm/app
 terminationGracePeriodSeconds: 0

# affinity pod
apiVersion: v1
kind: Pod
metadata:
 name: server1
spec:
 affinity:
  podAffinity:
   requiredDuringSchedulingIgnoredDuringExecution:
   - topologyKey: a-team
     labelSelector:
      matchExpressions:
      -  {key: type, operator: In, values: [web1]}
 containers:
 - name: container
   image: kubetm/app
 terminationGracePeriodSeconds: 0
```

#### Anti-Affinity

![podAntiAffinity](/devOps/kubernetes/image/podAntiAffinity.png)

여러 파드들을 집중되는 일 없이 분산되어 할당

마스터파드와 슬레이브 파드를 만들때 분산되어야 하는데 파드의 Type을 같은 파드로 설정해놓으면 서로 다른 노드에 할당해주도록 하는 기능

podAntiAffinity라는 옵션의 matchExpressions로 노드내의 파드라벨을 확인하고 topologyKey 옵션을 통해서 노드의 라벨의 조건을 줄 수 있다.
또한, Node Affinity와 마찬가지로 required/preferred옵션을 줄 수도 있다.

```yaml
# master
apiVersion: v1
kind: Pod
metadata:
  name: master
  labels:
     type: master
spec:
  nodeSelector:
    a-team: '1'
  containers:
  - name: container
    image: kubetm/app
  terminationGracePeriodSeconds: 0

# master-anti
apiVersion: v1
kind: Pod
metadata:
 name: slave
spec:
 affinity:
  podAntiAffinity:
   requiredDuringSchedulingIgnoredDuringExecution:
   - topologyKey: a-team
     labelSelector:
      matchExpressions:
      -  {key: type, operator: In, values: [master]}
 containers:
 - name: container
   image: kubetm/app
 terminationGracePeriodSeconds: 0
```

### 3. Node에 할당 제한

#### Toleration / Taint

![taint](/devOps/kubernetes/image/taint.png)

특정 노드에 아무 파드나 할당되지 않도록 제한을 하기 위해 사용

노드에 Taint를 지정해놓으면 스케줄러에 의해 할당되지도 않으며 수동으로 지정을 하려해도 할당되지 않는다. 파드에 Toleration을 설정해주어야 해당 노드에 할당이 가능하다.

#### Taint

노드에 Taint에서 labels와 effect옵션을 이용하여 설정할 수 있다.

Taint속성은 새로운 파드가 할당될때 확인하는 조건으로써 이미 노드에 파드가 돌아가고 있는 상태로 옵션을 추가해주게 되면 기존의 노드는 계속해서 작업을 수행할 수 있다.

effect

- NoSchedule : 타 파드들이 이 노드에 할당 되지 않는다.
- PreferNoSchedule : 가급적 스케줄링이 되지 않도록 하는 옵션으로 특정 상황에는 할당이 될 수도 있다.
- NoExecute : 기존의 작동하고있는 파드는 삭제되는 옵션

```sh
kubectl taint nodes k8s-node1 hw=gpu:NoSchedule #노드에 Taint 설정
kubectl taint nodes k8s-node1 hw=gpu:NoSchedule- #노드에 Taint 삭제
```

#### Toleration

파드에 해당 노드로 스케줄링 되도록 Toleration을 설정 해주어야 하며 key/operator/value/effect 속성으로 설정해줄 수 있다.

operator

- Euqal
- Exists

이 옵션을 파드에 주더라고 해당 파드는 다른 매칭되는 노드에 대해 스케줄링이 될 수 있기 때문에 `nodeSelector` 옵션을 추가로 주어 특정 노드에 할당될 수 있도록 해주어야 한다.

NoExcute노드에 NoExcute옵션을 단 파드라면 삭제가 되지 않겠지만 `tolerationSeconds`옵션을 이용해서 시간을 정의해주면 해당 시간 후에는 삭제하도록 할 수 있다.

```yaml
# NoScheduled pod
apiVersion: v1
kind: Pod
metadata:
 name: pod-with-toleration
spec:
 nodeSelector:
  gpu: no1
 tolerations:
 - effect: NoSchedule
   key: hw
   operator: Equal
   value: gpu
 containers:
 - name: container
   image: kubetm/app
 terminationGracePeriodSeconds: 0

# NoExcute pod
apiVersion: v1
kind: Pod
metadata:
 name: pod1-with-no-execute
spec:
 tolerations:
 - effect: NoExecute
   key: out-of-disk
   operator: Exists
   tolerationSeconds: 30
 containers:
 - name: container
   image: kubetm/app
 terminationGracePeriodSeconds: 0
```

<br>

### +) 추가

`terminationGracePeriodSeconds: 0` : 기본 pod의 삭제 요청후 삭제되는 시간은 30s인데 0s로 셋팅

<br><br>

## 파드 구조

![pod-architechture](/devOps/kubernetes/image/pod-architechture.PNG)

```yml
Status:
  phase: Pending
  conditions:
    - type: Initialized
      status: 'True'
      lastProbeTme: null
      lastTransitonTime: '2019-09-26T22:07:56Z'

    - type: PodScheduled
      status: 'True'
      lastProbTime: null
      lastTransitonTime: '2019-09-26T22:07:56Z'

containerStatuses:
  - name: container
    state:
      waiting:
        reason: ContainerCreating
    lastState: {}
    ready: false
    restartCount: 0
    image: tmkube/init
    imageID: ''
    started: false

  - type: ContainersReady
    status: 'False'
    lastProbTime: null
    lastTransitonTime: '2019-09-26T22:07:56Z'
    reason: ContainersNotReady
  - type: Ready
    status: 'False'
    lastProbTime: null
    lastTransitonTime: '2019-09-26T22:07:56Z'
    reason: ContainersNotReady
```

- Phase : Pod의 전체 상태
  - Pending
  - Running
  - Succeeded
  - Failed
  - Unknown
- Conditions : Pod가 실행하는 단계와 상태
  - Initialized
  - ContainerReady
  - PodScheduled
  - Ready
  - Reason : 컨디션의 상태가 False인경우 이유를 알려주기 위한 속성
    - ContainersNotReady
    - PodCompleted
- State : 각각의 컨테이너들을 대표하는 상태
  - Wating
  - Running
  - Terminated
  - Reason : 현재 상태의 이유
    - ConainerCreating
    - CrashLoopBackOff
    - Error
    - Completed

컨테이너의 상태중 imageID가 없는 경우 아직 image가 다운이 되지 않은 상태이다.

<br><br>

## LifeCycle

![pod-lifecycle](/devOps/kubernetes/image/pod-lifecycle.PNG)

![pod-lifecycle2](/devOps/kubernetes/image/pod-lifecycle2.PNG)

### 1. Pending

1. Pod의 최초상태로 컨테이너들이 생성되기 전에 초기화시켜줄 내용이 있을 경우 `initContainer`를 통해서 본 컨테이너보다 먼저 생성이 되어 볼륨/보안과 같은 셋팅을 수행할 수 있고 성공적으로 수행했거나 하지 않았다면 `Initialized`속성이 true, 실패했다면 false가 된다.

1. Pod가 올라가게 될 노드를 설정하는데 직접 설정하거나 k8s가 자동으로 잡아주게 되는데 완료가 된다면 `PodScheduled` 속성이 True가 된다.

1. Container에 image를 다운로드가 진행되고 컨테이너의 상태는 waiting(reason : ContainerCreating)이 된다.

+) Pending 도중에 Failed로 빠지는 경우도 존재하고 통신장애가 발생하는 경우 Unknown상태로 바뀌고 Unknown상태가 지속되면 Failed로 변경된다.

### 2. running

1. 컨테이너가 기동이되면서 Pod의 상태가 `Running`이 된다.

1. 만일 컨테이너가 기동이 되는 중 문제가 발생한다면 컨테이너의 상태난 waiting(reason : CrashLoopBackOff)이 되어 컨테이너를 재기동한다. 이상황에도 Pod의 상태는 Running상태이며 내부 `ContainerReady` / `Ready` 속성이 false로 바뀌게 된다.

1. 모든 컨테이너가 정상적으로 running이 되었다면 `ContainerReady` / `Ready`이 true가 된다. 이렇게 컨테이너에 문제가발생해도 `Running`상태이기 때문에 Pod의 상태뿐만이 아니라 컨테이너의 상태도 모니터링을 수행해야 한다.

+) 통신장애가 발생하는 경우 Unknown상태로 바뀌고 Unknown상태가 지속되면 Failed로 변경된다.

### 3. Failed / Succeeded

Job / CronJob으로 생성된 Pod의 경우 작업이 끝났을때 위 상태중 한개로 변경되게 되는데 만약 작업을 하고있는 컨테이너중 한개라도 문제가 발생해서 `Error`가 발생했다면 Failed, 모두 Completed가 되었다면 Succeeded상태가 된다.

이 두 상태 모두 컨테이너들은 종료된 상태이기 때문에 `ContainerReady` / `Ready` 는 모두 False가 된다.

<br><br>

## ReadinessProbe / LivenessProbe

컨테이너위에 올라가는 App의 상태를 감지하고 대응하기 위한 설정으로 서로 기능의 목적만 다를뿐 설정 방법은 동일하다.

#### 속성

- `httpGet` : Port, Host, Path, HttpHeader, Scheme등을 설정으로 체크
- `Exec` : Command를 통해 결과를 체크할 수 있다.
- `tcpSocket` : port, host를 이용해서 성공 여부를 확인할 수 있다.

반드시 위 3개의 옵션중 1개는 꼭 정의해야하는 속성이다.

<br>

#### 옵션

- initialDelaySeconds : 최초 Probe를 하기전에 딜레이 시간
- periodSeconds : Probe를 체크하는 간격
- timeoutSeconds : timeout 시간
- successThreshold : 몇번 성공해야 성공으로 인정할 것인지에 대한 값
- failureThreshold : 몇번 실패해야 실패로 인정할 것인지에 대한 값

위 설정을 통해 App의 성공여부를 파악하고 성공이 되기 전가지는 Pod의 상태가 Running이 되어도 컨테이너의 상태는 false로 Service는 NotReadyAddr 상태로 Pod와 연결이 되지 않는다.

```sh
kubectl get events -w | grep pod-readiness-exec1  #pod-readiness-exec1이라는 이름의 event들 조회
watch "kubectl describe pod pod-readiness-exec1 | grep -A5 Conditions" #pod-readiness-exec1라는 pod의 Conditions와 매칭되는 단어에서 5번째 줄까지 지속적으로 출력
kubectl describe endpoints svc-readiness  #Service의 endpoint상태 확인(pod와 연결상태 확인)
```

<br>

### 1. ReadinessProbe

![readinessProbe](/devOps/kubernetes/image/readinessProbe.PNG)

한 서비스가 2개의 Pod가 서로 다른 노드위에서 실행되고 있을때 한개의 노드가 문제가발생해서 한 파드가 죽었다면 auto healing 기능에 의해 새로운 파드가 생성이 되게 되는데 이때 파드와 컨테이너의 상태가 running이 되면 트래픽을 나누어 요청을 처리하게 된다. 그런데 컨테이너는 Running이지만 App이 아직 부팅중이라면 50%의 사용자는 에러를 응답받게 될 것이다.

이런경우와 같이 App 구동까지 트래픽을 나누지 않아 트래픽 실패를 없애는 기능

예를들어 톰캣과 같이 웹서버는 구동이 되어 Running상태가 되었는데 그 위에 올라가는 App이 구동이 아직 되지 않은 경우

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-readiness-exec1
  labels:
    app: readiness
spec:
  containers:
    - name: readiness
      image: kubetm/app
      ports:
        - containerPort: 8080
      readinessProbe:
        exec:
          command: ['cat', '/readiness/ready.txt']
        initialDelaySeconds: 5
        periodSeconds: 10
        successThreshold: 3
      volumeMounts:
        - name: host-path
          mountPath: /readiness
  volumes:
    - name: host-path
      hostPath:
        path: /tmp/readiness
        type: DirectoryOrCreate
  terminationGracePeriodSeconds: 0
```

### 2. LivenessProbe

![livenessProbe](/devOps/kubernetes/image/livenessProbe.PNG)

Pod와 Container는 Running상태인데 Memory Overflow와 같은 문제로 App만 죽은 경우에는 Auto Healing기능이 수행되지 않아 지속적인 실패를 발생시키게 되는데 App장애를 감지하고 Pod를 재실행시켜 트래픽의 지속적인 실패를 없애는 기능

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-liveness-httpget1
  labels:
    app: liveness
spec:
  containers:
    - name: liveness
      image: kubetm/app
      ports:
        - containerPort: 8080
      livenessProbe:
        httpGet:
          path: /health
          port: 8080
        initialDelaySeconds: 5
        periodSeconds: 10
        failureThreshold: 3
  terminationGracePeriodSeconds: 0
```

<br><br>

## QoS classes

![qos](/devOps/kubernetes/image/qos.PNG)

Quality of Service의 약자로 k8s에서는 앱의 중요도에 따라서 자원을 관리할 수 있도록 지원해주는 기능으로 한 파드에서 추가 자원이 필요할경우 해당 파드가 에러를 발생하는 것이 아닌 다른 파드의 자원을 다운시키고 필요한 파드에게 자원을 할당해줌으로써 관리를 해주는 기능이다.

QoS classes는 별도의 설정으로 할당을 하는 것이 아니라 spec의 resources를 정의해 줄때 `requests`, `limits`의 설정 값으로 단계가 설정이 된다.

### 1. Guaranteed

가장 높은 등급의 단계로 한 파드내 모든 request와 limit가 설정 되어 있고 reqeust와 limit에 memory와 cpu가 모두 설정되어 memory와 cpu의 request와 limit의 값이 모두 같은 경우 해당 등급이 설정된다.

### 2. Bustable

request내의 mem/cpu 값이 limit의 mem/cpu값보다 낮은 경우나, request만 설정된 경우, 파드내 한 컨테이너는 설정이 되었어도 다른 컨테이너가 설정이 안된 경우가 해당된다.

![oom](/devOps/kubernetes/image/oom.PNG)

등급이 같을경우 `OOM Score`에 따라서 해당 점수가 높은 파드가 먼저 다운된다.

> OOM Score
>
> Out Of Memory의 약자로 한마디로 사용량을 의미한다.
> <br>Request의 할당량에 비례해서 App이 사용하고 있는 량.

### 3. BestEffort

가장 먼저 다운되는 단계로 어떤 container에도 request와 limt가 미설정된 파드가 해당된다.

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
