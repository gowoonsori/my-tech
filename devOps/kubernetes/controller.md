![controller](/devOps/kubernetes/image/controller.PNG)

## 기능

1. auto healing
   특정 노드가 문제가 발생해서 그 노드 내의 파드가 문제가 발생하면 이를 감지하고 다른 노드에 파드를 옮겨준다.

1. auto scaling
   한 파드가 모든 자원을 limit상태가 되었을때 이를 파악하고 파드를 하나 더 만들어 줌으로써 부하를 분산 시켜준다.

1. software update
   파드들의 버전 업그레이드와 같은 경우 자동으로 업데이트 시켜주고 문제발생시 롤백기능도 제공한다.

1. job
   필요한 순간에만 파드를 만들어서 작업을 이행하고 삭제하는 것과 같이 스케줄링기능을 제공하여 자원을 효율적으로 제공한다.

<br>

## Replication Controller / ReplicaSet

![controller-attribute](/devOps/kubernetes/image/controller-attribute.PNG)

Replication Controller는 Deprecated되었고 그 후에 나온 것이 ReplicaSet이다.

### Template / Replicas

selector를 통해서 label로 컨트롤러와 파드를 연결 하게 되고 `template`로 특정 파드의 형태를 지정할 수 있고 만일 특정 파드가 삭제가 되면 다시 재생성하려는 특징을 가지고 있다. 그래서 template에 파드를 업그레이드해놓고 기존의 파드를 삭제해주면 파드를 재생성해주려는 특성때문에 자동으로 버전업그레이드된 파드를 재생성 하게 된다.

replicas는 최대 생성하는 파드의 수로 이 replicas를 늘려주게되면 scale out이 되게 되고 줄여주면 scale in이 된다.

이는 Replication Controller와 ReplicaSet모두 가지고있는 특성이다. 이런 특성들때문에 특정 파드를 생성하기보다는 컨트롤러 한개만 정의해서 사용하는 경우가 많다.

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-2
  lavels:
    type: web
spec:
  containers:
    - name: container
  image: tmkube/app:v1
```

```yml
apiVersion: v1
kind: ReplicationController
metadata:
  name: replication-1
spec:
  replicas: 1
  selector:
    type: web
  template:
    metadata:
      name: pod-1
      labels:
        type: web
      spec:
        containers:
          - name: container
        image: tmkube/app:v2
```

<br>

### Selector

이는 ReplicaSet에만 있는 기능으로 ReplicaSet에는 Replication Contorller와 달리 `matchLabels, matchExpressions`속성이 추가로 존재한다. Replication Controller에서 파드를 연결할때는 라벨의 key/value가 모두 동일한 파드만 연결이 가능하고 ReplicaSet에서는 matchLabels이 동일한 역할을 수행한다.

이때, matchExpressions은 key/value를 조금 더 디테일하게 컨트롤 할 수 있어 value는 달라도 key만 같은 파드를 선택할 수 있게 된다.

```yml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: replica-1
spec:
  replicas: 3
  selector:
    matchLabels:
      type: web
    matchExprssions:
      - { key: ver, operator: Exists }
  template:
    metadata:
      name: pod-1
      labels:
        type: web
      spec:
        containers:
          - name: container
        image: tmkube/app:v2
```

#### 다른 Operator들

![matchExpressions](/devOps/kubernetes/image/matchExpressions.PNG)

1. Exists : 특정 key가 일치하는 파드를 선택
1. DoesNotExist : 특정 key가 일치하지 않은 파드를 선택
1. In : 설정한 key와 일치하고 values가 포함된 파드들을 선택
1. NotIn : 설정한 key와 일치하고 values들이 포함되지 않은 파드들을 선택

<br>

## Deployment

![deployment](/devOps/kubernetes/image/deployment.PNG)

현재 한 서비스가 운영중일때 이 서비스를 업데이트해야되서 재배포를 해야할때 도움이 되는 컨트롤러

### ReCreate

![recreate](/devOps/kubernetes/image/recreate.PNG)

Deployment가 기존의 pod를 삭제하고 자원사용량이 없어지게 되고 새로 pod를 생성하는 방식으로 중간 downtime이 존재한다는 단점이 있다.

Deployment에서도 Controller와 동일하게 selector/replicas/template를 설정해주는데 이는 controller와 같이 파드를 생성/관리하기 위한 목적이 아니라 deployment가 생성하는 controller에 속성들의 값으로 전달하기 위한 값이다.

deployment의 template을 update하게 되면 기존의 replicaSet의 replicas는 0으로 변경하고 새로운 replicaSet을 생성한다.

```yml
apiVersion: app/v1
kind: Deployment
metadata:
  name: deployment-1
spec:
  selector:
    matchLabels:
      type: app
  replicas: 2
  strategy:
    type: Recreate
  revisionHistoryLimit: 1
  template:
    metadata:
      labels:
        type: app
    spec:
      continers:
        - name: container
          image: tmkube/app:v1
```

`revisionHistoryLimit`은 repliacas가 0인 controller를 남겨놓는 숫자로 default는 10이다. 이렇게 기존의 controller를 남겨놓는 이유는 이전 버전으로 rollback을 위함이다.

```sh
kubectl rollout undo deployment deployment-1 --to-revision=2 #deployment-1의 deployment의 vision을 2로 roll back
kubectl rollout history deployment deployment-1 #deployment-1이라는 이름의 deployment의 revision 기록
```

### Rolling update

![rolling-update](/devOps/kubernetes/image/rolling-update.PNG)

Deployment가 새로운 버전의 pod를 한개 만들어 준 후 요청을 새로운 pod도 더해서 같이 처리하게 해준 후 한개의 기존버전 pod를 삭제하는 방식으로 파드들을 차례로 업데이트 하는 방식인데 이는 downtime이 존재하지 않지만 추가 자원을 필요로 한다는 특징이 있다.

```yml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: deployment-2
spec:
  selector:
    matchLabels:
      type: app2
  replicas: 2
  strategy:
    type: RollingUpdate
  minReadySeconds: 10
  template:
    metadata:
      labels:
        type: app2
    spec:
      containers:
        - name: container
          image: kubetm/app:v1
      minReadySeconds: 10
```

`minReadySeconds` 옵션은 새로운파드를 생성하고 기존의 파드를 삭제하는 사이의 텀을 정의해주는 값이다.

이때 의문으로 새로생성된 ReplicaSet은 라벨을 가지고 파드를 연결하는데 기존의 파드들과도 연결될 수 있지 않을까 싶지만, 실제로는 replicaSet이 생성될때 컨트롤러마다 특정한 라벨이 붙게되고 이 라벨을 이용해서 새로운 파드를 만들때 추가적인 라벨을 추가하여 연결하기 때문에 기존의 파드들과는 연결되지 않는다.

### Blue/Green

Deployment를 사용해서 구성할 수도 있지만 ReplicaSet과 같이 replicas를 관리하는 controller를 이용해서 구성할 수 있다.

기존 버전의 파드들과 연결된 컨트롤러를 놔두고 새로운 버전의 파드들을 가진 컨트롤러를 생성하여 파드들을 관리하는 서비스에서 새로운 버전의 파드들로 새로 연결하는 방식으로 배포하는 방식

순간적으로 변경이 되기 때문에 downtime은 존재하지 않고 기존의 버전이 문제가 있을시 service의 라벨만 기존버전으로 수정하면 롤백이 쉽다는 장점이 존재하지만 자원이 두배가 필요하다는 특징이 있다.

```yml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: replica1
spec:
  replicas: 2
  selector:
    matchLabels:
      ver: v1
  template:
    metadata:
      name: pod1
      labels:
        ver: v1
    spec:
      containers:
        - name: container
          image: kubetm/app:v1
      terminationGracePeriodSeconds: 0
```

### Canary

![canary](/devOps/kubernetes/image/canary.PNG)

새로운 버전의 파드를 가지고있는 컨트롤러를 새로 생성해서 기존버전의 파드들과 같이 서비스에 연결시켜 새로운 버전에 대해 테스팅을 하는 식으로 배포하는 방식으로 새로운 버전이 문제가 있다면 컨트롤러의 replicas를 0으로 바꿔줌으로써 연결을 끊을 수 있다.

서비스에 기존의 라벨을 이용하여 붙여서 테스팅을 하는 것은 불특정 다수를 대상을 테스트하는 방식이고, 새로운 버전의 라벨을 가진 서비스를 한개 더만들고 Ingress Controller를 새로 만들어 기존의 서비스와 새로운버전의 서비스를 연결해서 특정조건에 대한 요청만 새로운 버전의 파드로 맵핑되도록해 특정된 다수를 대상으로 테스팅을 수행할 수 있다.

이처럼 테스팅 후 문제가 없다면 버전업그레이드를 하는 방식으로 donwtime이 존재하지 않고 추가자원은 정의한 파드의 개수에 따라 상이할 수 있다.

<br>

## DeamonSet / Job / CronJob

![controller2](/devOps/kubernetes/image/controller2.PNG)

### DeamonSet

![daemonset](/devOps/kubernetes/image/daemonset.PNG)
ReplicaSet은 노드별로 자원상태를 파악하고 그에 따라 유연하게 분배를 하게되지만 DaemonSet은 각 노드의 자원상태에 상관없이 각각의 노드에 한개씩 생성되는 특징이 있다.

이러한 특징을 사용하는 서비스에는 `성능 수집(모니터링)`, `로그 수집`, 노드들을 `storage`로써 네트워크 파일시스템으로 활용될 수 있고, 네트워크 프록시로써 사용될 수도 있다.

selctor와 template가 존재하여 라벨을 이용해 모든 노드에 템플릿으로 파드를 만들고 라벨로 파드들과 연결이 된다.

만약에 노드들이 os가 달라서 특정 파드가 특정 os에서는 동작하지 않아 특정 노드에는 생성을 하고 싶지 않다면 template의 파드설정으로 nodeSelector(os:centos)와 같이 특정 옵션을 이용해서 특정 조건에만 생성하도록 할 수 있다. 이처럼 마찬가지로 hostPort에 대해 해당 노드의 특정 port로 파드들을 접근할 수 있다.

```yml
apiVersion: apps/v1
kind: DaemonSet
metadata:
  name: daemonset-1
spec:
  selector:
    matchLabels:
      type: app
  template:
    metadata:
      labels:
        type: app
    spec:
      containers:
        - name: container
          image: kubetm/app
          ports:
            - containerPort: 8080
              hostPort: 18080
```

### Job

![job](/devOps/kubernetes/image/job.PNG)

일반 Pod생성을 통해 생성한 Pod는 노드에 문제가 생겼을때 같이 삭제되는 문제가 존재하고 controller을 통해 만들어진 파드는 노드가 문제가 발생해도 새로운 노드에 새로 생성이되며, 파드가 일을 하지 않으면 파드를 restart시켜주기 때문에 무슨일이 있어도 서비스가 수행되어야 하는 목적으로 사용된다.

Job은 controller처럼 노드에 문재가 발생해도 새로운노드에 파드를 생성해주는점에서는 같지만 일을 하지 않으면 파드가 종료가되고 삭제는 아니고 자원을 사용하지 않은 상태로 멈춰있는 상태가 된다. 특정 업무를 수행한 결과를 확인해야하기 때문에 파드에 들어가서 로그같은 데이터를 확인할 수 있다.

template와 selector가 존재하는데 selector는 만들지 않아도 알아서 만들어준다. completions 옵션을 주면 옵션만큼의 파드들이 순차적으로 실행되고 모두 종료되어야 job도 종료가 된다.

parallelism 옵션은 옵션만큼 파드가 같이 생성이되고 activeDeadlineSeconds옵션을 이용하면 특정 시간이 지나면 job이 삭제되고 job에 속하는 pod들도 실행이 되지 않는다. 이는 job의 마감기간을 설정하는 것으로 자원을 무한히 가지게 되는 경우를 방지할 수 있게 해준다.

```yml
apiVersion: batch/v1
kind: Job
metadata:
  name: job-1
spec:
  completions: 6
  parallelism: 2
  activeDeadlineSeconds: 30
  template:
    spec:
      restartPolicy: Never
      containers:
        - name: container
          image: kubetm/init
          command: ['sh', '-c', "echo 'job start';sleep 20; echo 'job end'"]
      terminationGracePeriodSeconds: 0
```

### CronJob

![cronjob](/devOps/kubernetes/image/cronjob.PNG)
![concurrency](/devOps/kubernetes/image/concurrency.PNG)

Job들을 시간에 따라서 생성하는 목적으로 사용되며 일종의 스케줄링같은 개념

`백업` / `업데이트 체크` / `메일/sms (message)`와 같은 기능에 사용될 수 있다.

schedule과 jobTemplate이 존재하며 schedule은 `cron format`이고 jobTemplate에 job을 명시해주면 된다.

concurrencyPolicy도 존재하는데 `allow`의 경우 기존의 job이 실행되고 이전 job의 파드가 종료되지 않아도 새로 생성하여 job을 이어가고 `forbid`의 경우에는 기존의 job이 끝나지 않았다면 새로운 job을 생성하지 않고 skip이 되고 파드가 종료되었을때 그 시점의 job을 새로 생성한다. `replace`는 기존의 job이 삭제되고 새로운 job을 만들어 job을 실행한다.

```yml
apiVersion: batch/v1beta1
kind: CronJob
metadata:
  name: cron-job
spec:
  schedule: '*/1 * * * *'
  concurrencyPolicy: Replace
  jobTemplate:
    spec:
      template:
        spec:
          restartPolicy: Never
          containers:
            - name: container
              image: kubetm/init
              command: ['sh', '-c', "echo 'job start';sleep 20; echo 'job end'"]
          terminationGracePeriodSeconds: 0
```

```sh
kubectl create job --from=cronjob/cron-job cron-job-manual-001 #cron-job-manual-001이라는 이름의 job을 cron-job의 template을 이용해서 job한개를 생성

kubectl patch cronjobs cron-job -p '{"spec" : {"suspend" : false }}' #suspend를 true로 수정
```

suspend가 true가 되면 cronJob은 job을 만들지 않는다.

<br><br>

## 추가

`kubectl delete replicationcontrollers replication1 --cascade=false` : replicationController를 삭제하더라도 이와 연결된 파드들을 삭제하지 않은 옵션으로 이를 이용해서 replicationContoller를 replicationSet으로 업데이트가 가능하다.

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
