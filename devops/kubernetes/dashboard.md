## v1.10.1
![dashboard-v1](/devops/kubernetes/image/dashboard-v1.PNG)

기존의 dashboard를 설치하면 dashboard pod가 생성되어 해당 serviceAccount와 cluster를 설치하면 기본적으로 생성되는 ClusterRole인 cluster-admin과 연결되어 api server에 접근 할 수 있었고 이를 proxy서버로 열어 외부에서 ip와 port번호만 알면 누구나 접속이 가능했다.

```sh
# kubetm 가이드로 Dashboard대로 설치했을 경우 아래 명령으로 삭제
kubectl delete -f https://kubetm.github.io/documents/appendix/kubetm-dashboard-v1.10.1.yaml

# 새 Dashboard (2.0.0) 설치 - <https://github.com/kubernetes/dashboard/releases/tag/v2.0.0>
kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.0.0/aio/deploy/recommended.yaml
```

## v2.0.0
![dashboard-v2](/devops/kubernetes/image/dashboard-v2.PNG)

proxy가 아닌 바로 api server에 접근하기 위해 kubeconfig파일을 만들고 인증서를 만들어 해당 token을 이용하여 접근하도록 하여 보안을 강화한 방법.

v2.0.0 이후에는 kubernetes-metrics-scraper라는 pod가 추가로 생성되어 자원의 대한 내용을 그래프로 표시될 수있도록 하는 역할을 하며 이때 같이 clusterRole/ClusterRoleBinding(kubernetes-dashboard)가 생성되어 serviceAccount에 연결되고 v1.10.1과 같이 cluster내 자원에 접근하기 위한 clusterRole과 ClusterRoleBinding에도 연결이 된다.

```sh
# kubetm 가이드로 Dashboard대로 설치했을 경우 아래 명령으로 삭제
kubectl delete -f https://kubetm.github.io/yamls/k8s-install/dashboard-2.3.0.yaml

# 다시 Dashboard (2.3.0) 설치 - <https://github.com/kubernetes/dashboard/releases/tag/v2.3.0>
kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.3.0/aio/deploy/recommended.yaml

#ClusterRoleBinding 생성
cat <<EOF | kubectl create -f -
apiVersion: rbac.authorization.k8s.io/v1beta1
kind: ClusterRoleBinding
metadata:
  name: kubernetes-dashboard2
  labels:
    k8s-app: kubernetes-dashboard
roleRef:
  apiGroup: rbac.authorization.k8s.io
  kind: ClusterRole
  name: cluster-admin
subjects:
- kind: ServiceAccount
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard
EOF

#token확인 (kubernetes-dashboard-token- 후에 tab쳐서 파일 완성시키고 명령어 실행)
kubectl -n kubernetes-dashboard get secret kubernetes-dashboard-token- \-o jsonpath='{.data.token}' | base64 --decode

#인증서 설치
grep 'client-certificate-data' ~/.kube/config | head -n 1 | awk '{print $2}' | base64 -d >> client.crt
grep 'client-key-data' ~/.kube/config | head -n 1 | awk '{print $2}' | base64 -d >> client.key
openssl pkcs12 -export -clcerts -inkey client.key -in client.crt -out client.p12 -name "k8s-master-30"

#외부에서 접속
https://192.168.0.30:6443/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/#/login
```

<br><br><br>

### Reference

[인프런-김태민님 강의](https://www.inflearn.com/course/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%EA%B8%B0%EC%B4%88/dashboard)
