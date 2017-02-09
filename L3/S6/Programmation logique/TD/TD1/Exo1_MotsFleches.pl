word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

motscroises(V1,V2,V3,H1,H2,H3):-
	word(V1,_,X1,_,Y1,_,Z1,_),
	word(V2,_,X2,_,Y2,_,Z2,_),
	word(V3,_,X3,_,Y3,_,Z3,_),
	word(H1,_,X1,_,X2,_,X3,_),
	word(H2,_,Y1,_,Y2,_,Y3,_),
	word(H3,_,Z1,_,Z2,_,Z3,_).