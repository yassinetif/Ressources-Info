/*not = non*/
non(0,1).
non(1,0).

/*xor - ou exclusif*/
xor(0,0,0).
xor(0,1,1).
xor(1,0,1).
xor(1,1,0).

/*or*/
or(0,0,0).
or(0,1,1).
or(1,0,1).
or(1,1,1).

/*and*/
and(0,0,0).
and(0,1,0).
and(1,0,0).
and(1,1,1).

/*nand = non et*/
nand(0,0,1).
nand(0,1,1).
nand(1,0,1).
nand(1,1,0).

/*circuit */
circuit(X,Y,Z):-non(X,S1),nand(X,Y,S2),xor(S1,S2,S3),non(S3,Z).
