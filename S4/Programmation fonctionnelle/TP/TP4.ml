(* DURAN Alizee - TP4 *)

(* Type arbre et type liste *)
type 'a arbre = V | N of ('a * 'a arbre * 'a arbre);;
type 'a liste = vide | cons of  'a* 'a liste;;

(* Identificateurs tete et suite pour liste *)
let rec tete = function cons(x,_) -> x
					| _ -> failwith "impossible";;
let rec suite = function cons(_,y) -> y
					| _ -> failwith "impossible";;

(* Question 1 *)
let rec ex1a = function V -> 0
				| N(r, ag, ad) -> snd r + ex1a ag + ex1a ad;;

let rec ex1l = function l -> if l=vide then 0
							else snd (tete l) + ex1l (suite l);; 

(* Question 2 *)
let plus = fun (a,b) (c,d) -> (c, b+d);;
let rec ex2a = fun c V -> N(c, V, V)
				| c (N(r,ag,ad)) -> if snd c = fst r then N((plus c r),ag,ad)
									else if snd c < fst r then N(r, ex2a c ag, ad)
									else N(r, ag, ex2a c ad);;

let rec ex2l = fun c l -> if l=vide then cons(c,vide)
							else if fst c = fst (tete l) then cons(plus c (tete l), (suite l))
							else if fst c < fst (tete l) then cons(c, l)
							else cons(tete l, ex2l c (suite l));;
									
(* Question 3 *)
let rec aux = fun V l -> l
				| (N(r,ag,ad)) l -> aux ag (cons(r,aux ad l));;
let ex3 = function a -> aux a vide;;

(* Question 4 *)
let max2 = fun (a,b) (c,d) -> if b > d then (a,b) else (c,d);;
let rec maxi = function V -> failwith "erreur"
							| N(r,V,V) -> r
							| N(r,ag,V) -> max2 r (maxi ag)
							| N(r,V,ad) -> max2 r (maxi ad)
							| N(r,ag,ad) -> max2 r (max2 (maxi ag) (maxi ad));;
