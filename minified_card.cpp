#include <iostream>                             // https://jellepelgrims.com/posts/business_card
#include <algorithm>                            // g++ card.cpp -o card && ./card && reset
typedef double d;typedef int i;i K(i x){return x*x;}i J=255;i* h(i w,i H){i* m=new i[w*H];i A=
200;d M=0;for(i z=0;z<A;z++){i X=rand()%w;i Y=rand()%H;i B=rand()%(26)+5;for(i x=0;x<w;x++){for(
i y=0;y<H;y++){d b=K(B)-(K(x-X)+K(y-Y));if(b>0){d n=m[y*w+x]+b;m[y*w+x]=i(n);M=n>M?n:M;}}}}for(i
l=0;l<=w*H;l++){i H=m[l];m[l]=i((H/M)*100);}return m;}struct R{i r,g,b;};R* c(i* m,i w,i H){d a=
*std::max_element(m,m+w*H);R* A=new R[w*H];for(i g;g<=w*H;g++){i v=i((m[g]/a)*J);R C={v,v,v};A[g
]=C;}for(i x=0;x<w;x++){for(i y=0;y<H;y++){R C=A[y*w+x];i h=m[y*w+x];A[y*w+x]=h<=5?R{0,0,40}:h<=
a*(.1)?R{C.r-10,C.g-10,C.b+40}:h<=a*(.2)?R{C.r+120,C.g+80,C.b+40}:h<=a*(.5)?R{C.r-10,C.g+20,C.b-
10}:h<=a*(.9)?R{C.r-40,C.g-50,C.b-40}:R{J,J,J};if(m[y*w+(x-1)]>m[y*w+x]){R C=A[y*w+x];d W=.85;C.
r*=W;C.g*=W;C.b*=W;A[y*w+x]=C;}}}return A;}struct P{d x,y;};R* r(i* H,R* C,P p,i h,i O,i s,i v,i
o,i S,i t,i T){R* B=new R[S*t];i a=h+H[i(p.y)*T+i(p.x)];for(i x=0;x<S;x++){for(i y=0;y<t;y++){B[
y*S+x]=R{86+y-x,213+y-x,J+y-x};}}for(i z=v;z>1;z--){P l={-z+p.x,-z+p.y};P u={z+p.x,-z+p.y};d U=(
u.x-l.x)/S;for(i x=0;x<S;x++){d n=(a-H[i(l.y)*T+i(l.x)])/d(z)*s+O;if(n>=t)continue;if(!n)n=0;for
(i y=i(n);y<i(t);y++){R c=C[i(l.y)*T+i(l.x)];if(z>o){d m=1-((o-z)/d(o))*1.5;c=R{i(c.r*m),i(c.g*m
),i(c.b*m)};}B[y*S+x]=c;}l.x+=U;}}return B;}i D(R* B,i w,i h){printf("\e[?25l\e[H");for(i y=0;y<
h;y+=2){for(i x=0;x<w;x++){R c=B[y*w+x];R k=B[(y+1)*w+x];printf(
"\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm▀",c.r,c.g,c.b, k.r,k.g,k.b);}}}i main(){i* A=h(200,800);P p=
{100,800};for(;p.y>i(100-2);p.y-=2){D(r(A,c(A,200,800),p,50,7,10,100,65,80,48,200),80,48);}}