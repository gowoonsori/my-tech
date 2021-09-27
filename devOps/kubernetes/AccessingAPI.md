![accessing](/devOps/kubernetes/image/accessing.PNG)

우리가 k8s를 설치할때 kubectl을 설치하여 cli를 통해 자원을 조회하는 것도 k8s api server에 접근하여 조회하게 되는데 cluster 밖의 관리자나 사용자가 접근하고자 할때는 `인증서`를 가지고 있는 사람만 https로 조회를 할 수 있고 관리자가 kubectl명령어로 `proxy`를 열어주었다면 http로 인증서 없이 접근이 가능하다. 
또한, kubectl을 cluster내뿐만이 아니라 밖에서도 설치가 가능한데 `Config`기능을 활용하여 여러개의 cluster에 접속이 가능하고 이러한 부분들을 `User Account`라고 한다.

만일 pod에서 api server에 접근하고자 하려고 하면 보안상 문제가 있게 되기 때문에 `Service Account`를 이용해 pod에서 api server에 접근할 수 있어 외부 pod에서도 접근이 가능하다.

## 1. Authentication
![authentication](/devOps/kubernetes/image/authentication.PNG)

### 1) X509 Client Certs
k8s 설치시에 `kubeconfig`라는 해당 cluster에 접근하기 위한 파일이 존재하고 인증서와 key등의 정보를 포함하고 있어 외부에서 client crt/key 를 포함하여 https요청으로 api server에 접근이 가능하다. 또한 kubectl 설치시에 내부적으로 kubeconfig를 복사하여 설정하기 때문에 kubectl을 통해 api server를 호출할 수 있고 Proxy옵션을 `accept-hosts`주면 kubectl이 인증서를 가지고 있기 때문에 사용자는 http요청으로 인증서없이 접근이 가능하다.

#### kubectl config setting
1. kubeadm / kubectl / kubelet 설치
`yum install -y --disableexcludes=kubernetes kubeadm-1.15.5-0.x86_64 kubectl-1.15.5-0.x86_64 kubelet-1.15.5-0.x86_64`

2. admin.conf 인증서 복사
```sh
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config
```
3. proxy 띄우기
`nohup kubectl proxy --port=8001 --address=192.168.0.30 --accept-hosts='^*$' >/dev/null 2>&1 &`

### 2) kubectl
외부에 kubectl을 설치하여 여러개의 cluster에 접근하고자 할때 해당 kubectl내의 각 cluster의 `kubeconfig`파일이 존재해야 한다. 

kubeconfig안에는 `clusters`, `users`, `contexts`등의 설정이 존재한다.
- clusters : 해당 항목으로 클러스터를 등록이 가능하다.
    - name : 클러스터 이름
    - url : 연결정보 ( ip )
    - ca : 인증서 파일
- users : 해당항목으로 사용자를 등록이 가능하다.
    - name : 사용자 이름
    - crt : 사용자 인증서 파일
    - key : 개인 키
- contexts : 클러스터와 user 연결 정보
    - name : 컨텍스트 이름
    - cluster : 연결할 클러스터 이름
    - user : 연결할 사용자 이름


```yml
#kubeconfig
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: LS0tLS1KVEUtLS0tLQo=
    server: https://192.168.0.30:6443
  name: cluster-a
- cluster:
    certificate-authority-data: LS0tLS1KVEUtLS0tLQo=
    server: https://192.168.0.50:6443
  name: cluster-b
contexts:
- context:
    cluster: cluster-a
    user: admin-a
  name: context-a
- context:
    cluster: cluster-b
    user: admin-b
  name: context-b
current-context: context-a
kind: Config
preferences: {}
users:
- name: admin-a
  user:
    client-certificate-data: LS0tLS1KVEUtLS0tLQo=
    client-key-data: LS0tLS1KVEUtLS0tLQo=
- name: admin-b
  user:
    client-certificate-data: LS0tLS1KVEUtLS0tLQo=
    client-key-data: LS0tLS1KVEUtLS0tLQo=
```

```sh
# 특정 context사용하도록 설정
kubectl config user-context context-A

# node 정보 조회
kubectl get nodes
```


### 3) Service Account
namespace를 만들게 되면 하나의 `default`라는 이름의 `ServiceAccount`가 만들어지고 이 ServiceAccount는 하나의 `Secret`을 가지고 있는데 내용으로는 `인증서`와 `token`값이 포함되어있다.

파드를 만들게 되면 이 ServiceAccount가 연결이 되고 Pod는 이 token값을 통해서 api server에 연결이 가능하고 해당 token값 만 안다면 외부에서도 접근이 가능하다.

```sh
#ServiceAccount 확인
kubectl describe -n nm-01 serviceaccounts
#Secret 확인
kubectl describe -n nm-01 secrets
```

```sh
#Pod 생성
cat <<EOF | kubectl create -f -
apiVersion: v1
kind: Pod
metadata:
  name: pod-1
  namespace: nm-01
  labels:
     app: pod
spec:
  containers:
  - name: container
    image: kubetm/app
EOF
```

## Authorization
k8s가 자원에 대한 권한을 지원하는 방법은 여러가지가 존재한다. (RBAC, ABAC, Webhok, Node)

### 1) RBAC
![rbac](/devOps/kubernetes/image/rbac.PNG)

k8s에는 `Node`, `PV`, `Namespace`와 같이 cluster 단위로 관리되는 자원과 `Pod`와 `Service`와 같이 namespace단위로 관리되는 자원이 존재하고 `ServiceAccount`, `Role`, `RoleBinding`도 생성이 가능하다. ServiceAccount의 Role과 RoleBinding을 어떻게 설정하느냐에 따라 같은 namespace의 자원만 접근하거나 cluster의 자원에 접근하도록 변경할 수 있다.
Role은 여러개를 만들 수 있고 각 Role에는 읽기/쓰기 권한을 줄 수 있으며, RoleBinding은 Role을 지정하는 자원으로써 Role은 한개만 지정이 가능하고 ServiceAccount는 여러개 지정이 가능하다.

ServiceAccount에서 cluster자원에 접근하기 위해서는 ClusterRole과 clusterRoleBinding이 생성되어야 가능하고 기능은 role과 rolebinding과 동일하다. 하지만 RoleBinding에서 clusterRoleBinding이 아닌 ClusterRole를 직접 지정이 가능한데 이경우에는 클러스터 자원에는 접근이 불가능하고 같은 namespace의 자원만 사용이 가능하다.

이는 role을 만들어사용하는 것과 동일한데 이렇게 사용하는 이유는 모든 namespace마다 똑같은 role을 부여하고 관리하는 상황에서 role의 내용이 변경이 되는 경우라면 모든 namespace를 하나하나 변경해주어야 하지만 이처럼 사용하면 clusterRole만 변경하면 되기 때문에 사용한다.

### 2) Role, RoleBinding