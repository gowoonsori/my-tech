![pod](/devOps/kubernetes/image/pod.PNG)
## 컨테이너
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

## 라벨
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

## 노드 스케줄
파드는 여러노드들 중에 한 노드에 올라가야되기 때문에 스케줄하는 방법이 두가지 존재한다.
### 직접 선택
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

### 쿠버네티스가 판단하여 스케줄러가 선택
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


<br><br>


## 추가
`terminationGracePeriodSeconds: 0` : 기본 pod의 삭제 요청후 삭제되는 시간은 30s인데 0s로 셋팅

<br><br><br>

---
### Reference
[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)