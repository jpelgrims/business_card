#include <iostream>
#include <algorithm>
#include <cmath>
typedef double d;typedef int i;i* h(i w,i H){i* m=new i[w*H]{0};i I=5;i a=30;i A=200;
for(i z=0;z<A;z++){i X=rand()%w;i Y=rand()%H;i B=rand()%(a-I+1)+I;for(i x=0;x<w;x++){
for(i y=0;y<H;y++){d b=pow(B,2)-(pow(x-X,2)+pow(y-Y,2));if(b>0){d n=m[y*w+x]+b;m[y*w+x
]=i(n);}}}}d M=*std::max_element(m,m+w*H);for(i x=0;x<w;x++){for(i y=0;y<H;y++){i H=m[
y*w+x];m[y*w+x]=i((H/M)*100);}}return m;}struct R{i r,g,b;};R* c(i* m,i w,i H){d a=*
std::max_element(m,m+w*H);R* A=new R[w*H];for(i x=0;x<w;x++){for(i y=0;y<H;y++){i v=
std::min(255,i((m[y*w+x]/a)*255));R C={v,v,v};A[y*w+x]=C;}}for(i x=0;x<w;x++){for (i y
=0;y<H;y++){R C=A[y*w+x];i h=m[y*w+x];A[y*w+x]=h<=5?R{0,0,40}:h<=a*(0.1)?R{C.r-10,C.g-
10,C.b+40}:h<=a*(0.2)?R{C.r+120,C.g+80,C.b+40}:h<=a*(0.5)?R{C.r-10,C.g+20,C.b-10}:h<=a
*(0.9)?R{C.r-40,C.g-50,C.b-40}:R{255,255,255};if(x>0&&x<w&&m[y*w+(x-1)]>m[y*w+x]){R C=
A[y*w+x];d W=0.85;C.r*=W;C.g*=W;C.b*=W;A[y*w+x]=C;}}}return A;}struct P{d x,y;};R* r(i
* H,R* C,P p,i h,i O,i s,i v,i o,i S,i t,i T){R* B=new R[S*t];i a=h+H[i(p.y)*T+i(p.x)]
;for(i x=0;x<S;x++){for(i y=0;y<t;y++){B[y*S+x]=R{86+y-x,213+y-x,255+y-x};}}for(i z=v;
z>1;z--){P pl={-z+p.x,-z+p.y};P pr={z+p.x,-z+p.y};d dx=(pr.x-pl.x)/S;for(i x=0;x<S;x++
){d hs=(a-H[i(pl.y)*T+i(pl.x)])/d(z)*s+O;if(hs>=t){continue;}if(!hs){hs=0;}for(i y=
floor(hs);y<floor(t);y++){R c=C[i(pl.y)*T+i(pl.x)];if(z>o){d m=1-((o-z)/d(o))*1.5;c=R{
i(c.r*m),i(c.g*m),i(c.b*m)};}B[y*S+x]=c;}pl.x+=dx;}}return B;}void D(R* B,i w,i h){
printf("\e[?25l\e[H");for(i y=0;y<h;y+=2){for(i x=0;x<w;x++){R c=B[y*w+x];R k=B[(y+1)*
w+x];printf("\e[38;2;%d;%d;%dm",c.r,c.g,c.b);printf("\e[48;2;%d;%d;%dm▀",k.r,k.g,k.b);
}}fflush(stdout);}i main(){srand(0);i* A=h(200,800);P p={100,800};for(;p.y>i(100-2);p.
y-=2) {D(r(A,c(A,200,800),p,50,7,10,100,65,80,48,200),80,48);}printf("\e[0m");}