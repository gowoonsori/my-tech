#include <iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

template<typename T>
struct MAXHEAP{
    private:
        vector <T> h;
    public:
        void push(T item){
            int i = h.size();
            h.push_back(item); //제일 뒤에 삽입
            while(i!=0 && h[i]>h[(i-1)/2]){
                swap(h[i],h[(i-1)/2]);
                i = (i-1)/2;
            }
        }
        T pop(){
            if(h.size()==0){
                cout<<"Heap is empty."<<endl;
                exit(1);
            }
            int val=h[0];
            h[0]=h[h.size()-1];
            h.pop_back();
            int p = 0;

            while(1){
                int child = p*2+1;  //왼쪽 child

                if(child>=h.size()) break;  //child가 더이상 없다면
                if(h[child]<h[child+1]){  //오른쪽 child가 더 크다면
                    child++;
                } 
                if(h[child]>h[p]){       //child의 값이 더 크다면 swap
                     swap(h[child],h[p]);
                     p=child;
                }
                else break;     //해당 값이 더 크다면 break
            }
            return val;
        }
        int heapsize(){return h.size();}
};

int main(){
    MAXHEAP<int> H;
    srand((unsigned int)time(NULL));

    for(int i=0;i<20;i++){
        H.push(rand()%100);
    }
    
    int i=1;
    while(H.heapsize()!=0)cout << i++ <<". "<< H.pop() << endl;

    return 0;
}