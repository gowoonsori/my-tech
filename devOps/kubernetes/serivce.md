# 명령어

## Get

```sh
kubectl get service svc-3 -n defalut
```

# Type

![type](/devOps/kubernetes/image/service.PNG)

## ClusterIp

서비스는 기본적으로 자신의 클러스터 ip주소를 가지고 있고 이를 파드에 연결시켜 놓으면 해당 ip주소를 이용해서 접근할 수 있다. 파드도 별도의 ip주소를 가지고 있지만 이는 휘발성 ip주소이기 때문에 신뢰성이 떨어지지만 서비스로 연결시켜놓으면 재생성이 되더라도 접근을 할 수 있게 된다.

서비스가 가지는 ip주소도 외부에서는 접근 할수 없으며 클러스터 내에서만 접근이 가능하고 여러개의 파드를 연결시켜놓아서 부하분산도 수행할 수 있다.

```yml
apiVersion: v1
kind: Service
metadata:
  name: svc-1
spec:
  selector:
    app: pod
  ports:
    - port: 9000
      targetPort: 8080
  type: ClusterIP
```

type옵션에서 ClusterIP는 옵셔널한 값으로 기본값이 ClusterIp이기 때문에 명시해주지 않아도 기본적으로 이 값을 갖게 된다. 위 yml은 9000번포트의 요청을 파드의 8080포트로 연결시켜준다는 내용이다.

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-1
  lables:
    app: pod
spec:
  continaers:
    - name: container
      image: tmkube/app
      ports:
        - coninaerPort: 8080
```

외부에서 접근할 수가 없고 클러스터내에서만 사용하는 ip로 운영자와 같이 인가된 사용자만 접근할 수 있기 때문에 `내부 대시보드`나 `파드의 서비스 상태 디버깅`할때 사용한다.

## NodePort

클러스터에 연결되어있는 모든 노드에 특정 포트를 할당하여 특정 노드에서 할당된 포트로 연결을 시도할때 노드들이 해당 서비스로 연결이 되고 서비스에 연결된 파드에게 역할을 보내주게 된다.

```yml
apiVersion: v1
kind: Service
metadata:
  name: svc-2
spec:
  selector:
    app: pod
  ports:
    - port: 9000
      targetPort: 8080
      nodePort: 30000
  type: NodePort
```

nodePort는 30000~32767사이의 포트중에 선택할 수 있고 명시하지 않으면 이 값중 한 값으로 자동으로 설정이 된다.

<br>

기본적으로는 어떤 특정노드를 통해서 접근을 해 요청을 하더라고 서비스는 1번노드내에 존재하는 파드를 수행하는 것이 아니라 서비스가 판단하여 적절한 다른 노드의 파드를 할당하게 되는데 `externalTrafficPolicy: Local` 옵션을 주면 특정 노드를 통해 접근한 요청은 해당 노드내의 파드를 수행하도록 해줄 수 있다.

<br>

물리적인 호스트에 ip를 통해서 파드에 접근할 수 있는 특징을 가지고 있는데 보통 호스트ip는 내부망에서만 접근할 수 있게 네트워크를 구성하기 때문에 내부망을 연결할때나 데모나 임시 연결용으로 사용한다.

## LoadBalancer

기본적으로 노드포트의 옵션을 가지고 있으며, 노드들 앞에 로드밸런서가 하나 생성이 되고, 로드밸런서가 부하분산을 통해 여러 노드들로 요청을 보낼 수 있다. 이때 외부에서 접근할 수 있도록 해주는 로드밸런서의 ip주소는 자동으로 생성이 되지 않기 때문에 별도로 외부접속 ip를 할당해주는 plugin이 설치가 되어있어야 ip주소가 할당된다. 만약 aws, google등을 통해서 만든다면 해당 plugin이 설치가 되어있어 ip주소가 할당 된다.

```yml
apiVersion: v1
kind: Service
metadata:
  name: svc-3
spec:
  selector:
    app: pod
  ports:
    - port: 9000
      targetPort: 8080
  type: LoadBalancer
```

실제적으로 외부에 시스템을 노출시킬때 내부ip를 노출시키지 않고 외부ip만을 노출 시켜 사용될 수 있다.

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
