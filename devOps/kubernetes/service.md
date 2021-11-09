## 1. 명령어

### 1) Get

```sh
kubectl get service svc-3 -n defalut #service 조회
```

```sh
# Pod이름이 request-pod인 Container로 들어가기 (나올땐 exit)
kubectl exec request-pod -it /bin/bash
```



## 2. Type

![type2](/devops/kubernetes/image/type.PNG)
![type1](/devops/kubernetes/image/serviceType.PNG)

### 1) ClusterIp

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

### 2) NodePort

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

물리적인 호스트에 ip를 통해서 파드에 접근할 수 있는 특징을 가지고 있는데 보통 호스트ip는 내부망에서만 접근할 수 있게 네트워크를 구성하기 때문에 `내부망을 연결`할때나 `데모`나 `임시 연결용`으로 사용한다.

### 3) LoadBalancer

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


## 3. Objects
![objects](/devops/kubernetes/image/service-object.PNG)
위의 type이 k8s의 service에 연결하여 node에 접속하기 위함이었는데 이는 service가 만들어지고 난 후에 그 ip를 이용해서 접근하는 방법이었지만 service의 pod가 동시에 여러개 배포되고 한 pod에서 다른 pod를 연결하고자 할때 pod의 ip는 동적할당이며 재생성시 변경이되기 때문에 접근이 힘들 수 있는데 이럴때 제공하는 object를 이용해 해결할 수 있다.
### 1) Headless

cluster 내에 dns가 존재하여 pod에서 service를 연결할때 service이름으로 연결이 가능했었는데 pod와 pod간의 연결도 headless옵션을 이용하면 dns에 `pod이름.service이름`의 이름으로 필드가 생성되어 ip가 관리되기 때문에 pod간에 연결이 가능하다.

![headless-clusterip](/devops/kubernetes/image/headless-clusterip.PNG)
service를 clusterIP방식으로 생성을 하게 되면 DNS가 위에 사진과 같이 생성이 되는데 보면 `service이름.namespace이름.종류(service/pod...).dns이름`의 규칙으로 domain이름이 생성되는데 이를 `FQDN(Fully Qualified Domain Name)`이라고 한다.
그리고 한 namespace에서 service는 이름만으로 접근이 가능하지만 pod는 전체 이름으로 조회를 해야하고 pod의 domain name이 동적으로 생성된 ip주소가 붙어 지정이 되기 때문에 pod이름으로 domain을 질의가 불가능해 pod에는 접근이 불가능하다.

![headless](/devops/kubernetes/image/headless.PNG)
service의 clusterIP를 `None`으로 하여 clusterIp를 만들지 않고 pod의 `hostname`에 domain을, `subdomain`에 service이름을 넣어 생성해주면 headless로 생성이 된다. 그렇게 되면 특정 이름으로 dns에 domain들이 생성이 되고 이 이름을 가지고 접근을 할 수 있다.

```yml
#Service
apiVersion: v1
kind: Service
metadata:
  name: headless1
spec:
  selector:
    svc: headless
  ports:
    - port: 80
      targetPort: 8080    
  clusterIP: None
```
```yml
#Pod
apiVersion: v1
kind: Pod
metadata:
  name: pod4
  labels:
    svc: headless
spec:
  hostname: pod-a
  subdomain: headless1
  containers:
  - name: container
    image: kubetm/app
```

### 2) Endpoint
![label-endpoint](/devops/kubernetes/image/label-endpoint.PNG)
우리가 service에서 pod를 연결할때 `label`을 이용하여 연결하였는데 이는 내부적으로 endpoint를 이용하여 연결된 방식이다. k8s는 서비스의 이름으로 endpoint를 생성하고 내부에 pod에 접속정보를 입력하여 service-pod 연결을 관리한다.

![endpoint](/devops/kubernetes/image/endpoint.PNG)
이를 이용하여 직접 endpoint를 설정해서 특정 pod나 외부 주소에 접근을 할 수 있다.


```sh
kubectl describe endpoints endpoint2  #enpoint 보기
```
```yml
#Service
apiVersion: v1
kind: Service
metadata:
  name: endpoint2
spec:
  ports:
  - port: 8080
```
```yml
#Pod
apiVersion: v1
kind: Pod
metadata:
  name: pod9
spec:
  containers:
  - name: container
    image: kubetm/app
```
```yml
apiVersion: v1
kind: Endpoints
metadata:
  name: endpoint2
subsets:
 - addresses:
   - ip: 20.109.5.12
   ports:
   - port: 8080
```

### 3) ExternalName
외부 ip주소를 알고 있어 endpoint를 이용하여 접근을 하더라도 이 외부 ip는 변경가능성이 있기 때문에 domain이름을 지정하는 방법이 필요한데 이때 사용할 수 있는 방법이다.

![externalName](/devops/kubernetes/image/externalName.PNG)
service를 생성할때 ExternalName속성에 domain이름을 지정해주면 dns cache가 내부/외부 DNS에서 주소를 찾아 연결해주기 때문에 ip주소가 바뀌어도 접속이 가능하다.

```yml
apiVersion: v1
kind: Service
metadata:
 name: externalname1
spec:
 type: ExternalName
 externalName: github.github.io
```


## 추가
k8s v1.11 이전에는 kube-dns 를 기반으로 DNS 서비스를 제공, 이후에는 CoreDNS를 도입했다.(보안과 안정성 문제)

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)

[k8s 공식문서](https://kubernetes.io/ko/docs/reference/kubectl/cheatsheet/)