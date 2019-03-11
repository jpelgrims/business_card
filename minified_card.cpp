#include <iostream>                  // https://jellepelgrims.com/posts/business_card
#include <algorithm>                 // g++ card.cpp -o card && ./card && reset
typedef double d;typedef int i;i K(i x){return x*x;}i J=255;i W=200;i H=800;i E=80;i 
F=48;i* h(){i* m=new i[W*H];d M=0;for(i z=0;z<W;z++){i X=rand()%W;i Y=rand()%H;i B=
rand()%(26)+5;for(i x=0;x<W;x++){for(i y=0;y<H;y++){d b=K(B)-(K(x-X)+K(y-Y));if(b>0){
d n=m[y*W+x]+b;m[y*W+x]=i(n);M=n>M?n:M;}}}}for(i l=0;l<=W*H;l++){i H=m[l];m[l]=i((H/M
)*100);}return m;}struct R{i r,g,b;};R* c(i* m){d a=*std::max_element(m,m+W*H);R* A=
new R[W*H];for(i g;g<=W*H;g++){i v=i((m[g]/a)*J);R C={v,v,v};A[g]=C;}for(i x=0;x<W;x
++){for(i y=0;y<H;y++){R C=A[y*W+x];i h=m[y*W+x];A[y*W+x]=h<=5?R{0,0,40}:h<=a*(.1)?R{
C.r-10,C.g-10,C.b+40}:h<=a*(.2)?R{C.r+120,C.g+80,C.b+40}:h<=a*(.5)?R{C.r-10,C.g+20,C.
b-10}:h<=a*(.9)?R{C.r-40,C.g-50,C.b-40}:R{J,J,J};if(m[y*W+(x-1)]>m[y*W+x]){R C=A[y*W+
x];d w=.85;C.r*=w;C.g*=w;C.b*=w;A[y*W+x]=C;}}}return A;}struct P{d x,y;};R* r(i* H,R*
C,P p,i o){R* B=new R[E*F];i a=50+H[i(p.y)*W+i(p.x)];for(i x=0;x<E;x++){for(i y=0;y<F
;y++){B[y*E+x]=R{86+y-x,213+y-x,J+y-x};}}for(i z=100;z>1;z--){P l={-z+p.x,-z+p.y};P u
={z+p.x,-z+p.y};d U=(u.x-l.x)/E;for(i x=0;x<E;x++){d n=(a-H[i(l.y)*W+i(l.x)])/d(z)*10
+7;if(n>=F)continue;if(!n)n=0;for(i y=i(n);y<i(F);y++){R c=C[i(l.y)*W+i(l.x)];if(z>o)
{d m=1-((o-z)/d(o))*1.5;c=R{i(c.r*m),i(c.g*m),i(c.b*m)};}B[y*E+x]=c;}l.x+=U;}}return 
B;}i D(R* B){printf("\e[?25l\e[H");for(i y=0;y<F;y+=2){for(i x=0;x<E;x++){R c=B[y*E+x
];R k=B[(y+1)*E+x];printf("\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm▀",c.r,c.g,c.b, k.r,k.g,
k.b);}}}i main(){i* A=h();P p={100,H};for(;p.y>i(98);p.y-=2){D(r(A,c(A),p,65));}}