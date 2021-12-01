![use case](/devops/kubernetes/image/useCase.PNG)

## ConfigMap / secret

컨테이너에서 특정 서비스들을 생성할때 특정 환경변수 하나가 달라도 다른 서비스로 이러한 서비스들을 각각 다른 Image로 관리하게 되면 어마어마하게 많은 image들을 관리하게 되는데, 이때 이런 값들은 미리 정의해두고 환경변수가 비어있는 이미지 한개만 관리를해도 이 설정파일을 같이 서비스를 생성하게 되면 여러 서비스들을 생성할 수 있게된다. 이때 configMap과 secret을 사용한다.

secret은 데이터가 메모리에 저장되기 때문에 보안에 유리하지만 시크릿당 최대 1M까지만 저장이 가능하다.

이때 환경변수를 여러 형태로 넣어 사용할 수 있다.

![env](/devops/kubernetes/image/env.PNG)

### Env(Literal)

ConfigMap을 통해 필요한 값을 상수로 설정해두고 컨테이너에서 값들을 사용할 수 있고 secret은 주요한 정보를 저장하는데 이때 secret의 value는 base64로 인코딩해서 값을 넣어주어야한다. 파드로 값이 주입이 될때는 자동적으로 디코딩이 되어 사용된다.

일반적인 object값들은 k8s db에 저장이 되는데 secret은 메모리에 저장이 되고 configMap은 key/value를 무한히 생성할 수 있지만 secret은 1mbyte만 사용이 가능하다.

```yml
apiVersion: v1
kind: ConfigMap
metadata:
  name: cm-dev
data:
  SSH: 'false'
  User: dev
```

```yml
apiVersion: v1
kind: Secret
metadata:
  name: sec-dev
data:
  Key: MTIzNA==
```

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-1
spec:
  containers:
    - name: container
      image: kubetm/init
      envFrom:
        - configMapRef:
            name: cm-dev
        - secretRef:
            name: sec-dev
```

## Env(File)

값으로 상수가 아닌 파일을 정의할때는 대시보드에서 제공하지 않기 때문에 직접 cli로 configMap/secret에 value로 값을 넣어주어야 한다.

```sh
echo "Content" >> file-c.txt
kubectl create configmap cm-file --from-file=./file-c.txt
```

```sh
echo "Content" >> file-s.txt
kubectl create secret generic sec-file --from-file=./file-s.txt
```

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-file
spec:
  containers:
    - name: container
      image: kubetm/init
      env:
        - name: file-c
          valueFrom:
            configMapKeyRef:
              name: cm-file
              key: file-c.txt
        - name: file-s
          valueFrom:
            secretKeyRef:
              name: sec-file
              key: file-s.txt
```

## Volume Mount (File)

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-mount
spec:
  containers:
    - name: container
      image: kubetm/init
      volumeMounts:
        - name: file-volume
          mountPath: /mount
  volumes:
    - name: file-volume
      configMap:
        name: cm-file
```

환경변수 방식은 한번 주입하면 끝이기 때문에 환경변수 값이 변경되어도 이를 사용하고있는 파드는 재주입하지 않은 이상 변경이 되지 않지만, 마운트방식은 말그대로 마운트를 해서 사용하기때문에 파일값이 변경되면 이를 사용하고 있는 파드는 바뀐 값을 사용하게 된다.

<br><br>

![object2](/devops/kubernetes/image/object2.PNG)

## NameSpace / Resource Quota/ LimitRange

한 클러스터 내에서는 여러 네임스페이스들을 만들 수 있고 네임스페이스 내에서는 여러 파드들을 만들어 사용할 수 있다. 이때 한 네임스페이스의 파드가 서버의 모든 자원을 사용하게 되면 다른 파드들에서 문제가 발생할 수 있기 때문에 네임스페이스들마다 최대 자원량을 제한하는 Resource Quota를 둘 수 있고 한 네임스페이스내에서 한개의 파드가 모든 Resource Quota만큼을 사용하고있다면 다른 파드들이 들어올 수 없기 때문에 한파드당 생성될 수 있는 자원량을 제한할 수 있는 LimitRange가 존재한다.

![namespace](/devops/kubernetes/image/namespace.PNG)

### NameSpace

한 네임스페이스에서는 같은 이름의 파드들을 중복해서 생성할 수없고, 타 네임스페이스 들과는 분리되어 관리되기 때문에 서로 다른 네임스페이스라면 한 서비스에서 다른 파드들을 연결할 수 없다. 그리고 네임스페이스를 지우게 되면 그 안에 모든 자원은 같이 지워지게 된다.

물론, PV나 node를 이용하여 연결을 할 수는 있고 연결은 되지 않지만, 각 파드가 가지고있는 내부 ip주소를 이용해서 접근과 연결은 가능하고 nodePort도 마찬가지이다. 이는 

```yml
apiVersion: v1
kind: Namespace
metadata:
  name: nm-1
```

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-1
  namespace: nm-1
```

```sh
# nm-3의 Namespace에 있는 ResourceQuota들의 상세 조회
kubectl describe resourcequotas --namespace=nm-3
# nm-5의 Namespace에 있는 LimitRange들의 상세 조회
kubectl describe limitranges --namespace=nm-5
```

## ResourceQuota

네임스페이스의 자원을 제한하기 위한 object로 ResourceQuota를 명시한 네임스페이스에 파드를 생성하려고할때 파드의 자원량을 명시해주지 않으면 새로 생성할 수 없고 현재 자원을 초과해도 생성이 되지 않는다.

네임스페이스말고도 클러스터 전체에 부여할 수 있는 권한이다.

```yml
apiVersion: v1
kind: ResourceQuota
metadata:
  name: rq-1
  namespace: nm-1
spec:
  hard:
    requests.memory: 3Gi
    limits.memory: 6Gi
```

memory 뿐만이 아니라 cpu, storage도 제한 할 수 있으며 object들의 숫자도 제한할 수 있지만 k8s버전마다 제한할 수 있는 object종류는 상이하다.

```yml
apiVersion: v1
kind: Pod
metadata:
  name: pod-2
spec:
  continers:
    - name: container
      image: tmkube/app
  resources:
    requests:
      memory: 2Gi
    limits:
      memory: 2Gi
```

## LimitRange

각각의 파드마다 네임스페이스에 들어갈 수 있는지 체크하기 위한 object

이는 resourceQuota와 달리 네임스페이스내에서만 사용이 가능한 object이다.

```yml
apiVersion: v1
kind: LimitRange
metadata:
  name: lr-1
spec:
  limits:
    - type: Container
      min:
        memory: 0.1Gi
      max:
        memory: 0.4Gi
      maxLimitRequestRatio:
        memory: 3
      defaultRequest:
        memory: 0.1Gi
      default:
        memory: 0.2Gi
```

```sh
kubectl describe limitranges --namespace=nm-5
```

<br><br><br>

---

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
