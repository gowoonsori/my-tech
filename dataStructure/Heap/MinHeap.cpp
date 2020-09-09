#include <iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;
/*vector를 사용하여 구현
 노드는 배열의 1번 부터 아닌 0번부터 이용
  부모 노드         =  (child-1)   / 2
  왼쪽 child 노드   =  부모노드* 2 + 1
  오른쪽 child 노드 =  부모노드 * 2 + 2  */

template<typename T>
struct MAXHEAP{
    private:
        vector <T> h;     
    public:
        void push(T item){
            h.push_back(item);     //제일 뒤에 삽입

            int curr = h.size()-1;
            /*첫번째 노드가 아니고 부모보다 작다면 */
            while(curr!=0 && h[(curr-1)/2]>h[curr]){
                swap(h[(curr-1)/2],h[curr]);
                curr= (curr-1) / 2;
            }
        }
        T pop(){    
            if(h.size()==0) {
                cout << "Heap is empty" << endl;
                exit(1);
            }
            T val = h[0];
            h[0]=h[h.size()-1];  //마지막 노드의 값을 첫번째로 옮기면서 마지막 노드 삭제
            h.pop_back();
            int curr=0;

            while(1){
                int child= curr * 2 + 1;

                if(child > h.size()) break;  //child가 없다면 break
                if(h[child] > h[child+1] ) child++;    //오른쪽 child가 더 작다면 오른쪽 child를 교체 대상
                if(h[curr] > h[child]) {
                    swap(h[curr],h[child]);    //현재 노드가 child보다 크다면 swap
                    curr = child;
                }
                else break;
            }
            return val;
            
        }
        int heapSize(){return h.size();}
};

int main(){
    MAXHEAP<int> H;
    srand((unsigned int)time(NULL));

    for(int i=0;i<20;i++){
        H.push(rand()%100);
    }

    int i=1;
    while(H.heapSize()!=0){
        cout.width(3);
        cout << i++ <<". ";
        cout.width(2);
        cout << H.pop() << endl;
    }

    return 0;
}