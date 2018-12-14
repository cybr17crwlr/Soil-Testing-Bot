import math




print("Enter the input of soil testing\n")
n1=float(input())
p1=float(input())
k1=float(input())
print("Enter U to put the inputs of crop requirement\n")

print("Enter X,Y or Z for respective crops\n")
ch=input()

if ch=='U':
	n=float(input())
	p=float(input())
	k=float(input())
#if ch=='X':
	#n=,p=,k=
#if ch=='Y':
	#n=,p=,k=
#if ch=='Z':
	#n=,p=,k=


n=n-n1
p=p-p1
k=k-k1

if n<0:
	print("No need of fertiliser as N is in excess amount")
	quit() 


#print(n,p,k)	
n=round(n*1000)/1000
p=round(p*1000)/1000
k=round(k*1000)/1000
N=int(n*1000)
P=int(p*1000)
K=int(k*1000) 

a=int(math.gcd(N,P))
b=int(math.gcd(N,K))
c=int(math.gcd(K,P))
LCM=int(min(a,b))
LCM=int(min(LCM,c))


N=float(N/LCM)
P=float(P/LCM)
K=float(K/LCM)


num=int(input())
an = {}
ap = {}
ak = {}
sum1={}
least=100000000.0
for i in range(num):
	an[i]=float(input())
	ap[i]=float(input())
	ak[i]=float(input())
	sum1[i]=abs(ap[i]-an[i]*P/N)+abs(ap[i]-an[i]*K/N)
	if least>sum1[i]:                                  
		least=sum1[i]
		pos=i+1
#print(pos)  

an1=an[pos-1];
#print(an1)
ap1=ap[pos-1];
ak1=ak[pos-1];
  
F=float(n*100/an1)

l=float(input())
w=float(input())
area=l*w/100
T=float(F*area)

C=T*2
print(C)
