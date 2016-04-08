(* DURAN Alizee - TP Syracuse *)

let suivant = function n -> if n mod 2=0 then n/2
							else n*3+1;;

(* Fonctions duree et hauteur de récursion normale *)
let rec duree = function n -> if n <= 0 then failwith "impossible"
							else if n=1 then 0
							else 1+duree(suivant(n));;
duree 23;;

let max = fun (a, b) -> if a > b then a else b;;
let rec hauteur = function n -> if n<=0 then failwith "impossible"
								else if n=1 then 1 
								else max(n, hauteur(suivant n));;

hauteur 53;;								

(* Et leur fonctions récursives terminales *)
let rec dureeterm = fun n res -> if n<=0 then failwith "impossible"
										else if n=1 then res
										else 1+res+dureeterm(suivant(n)) res;;
dureeterm 23 0;;
		
let rec hauteurterm = fun n res -> if n<=0 then failwith "impossible"
											else if n=1 then res
											else max(n, hauteurterm(suivant n) res);;
hauteurterm 53 1;;
