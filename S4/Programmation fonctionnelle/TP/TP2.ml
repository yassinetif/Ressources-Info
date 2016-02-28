(* DURAN Alizee - TP2 *)

(* Contenu de lire.ml *)
type 'a liste = vide | cons of  'a* 'a liste;;
let rec lignes = function canal ->
          try let une_ligne = input_line canal in
                cons(une_ligne, lignes canal)
          with End_of_file -> vide;;
let lire = function nom ->
       let canal = open_in nom in
          let resu = lignes canal in
               close_in canal; resu;;


(* Exercice 1 *)
let rec tete = function cons(x,_) -> x
					| _ -> failwith "impossible";;
let rec suite = function cons(_,y) -> y
					| _ -> failwith "impossible";;
let rec lire_liste = function l -> if l=vide then failwith "impossible"
							else cons(lire (tete l), lire_liste (suite l));;
let rec somme = function l -> if l=vide then 0
							else int_of_string(tete(l)) + somme(suite (l));;
lire "donnees.dat";;
somme(lire "donnees.dat");;

(* Exercice 2 *)
let rec trans = function (cons (n,cons(i, reste))) -> cons((n,int_of_string(i)), trans reste)
					 | vide -> vide
					 | _ -> failwith "element manquant";;


(* Exercice 3 *)
let rec exo3 = fun c l -> if l=vide then 0
								
								else if c = fst (tete l) then snd(tete l) + exo3  c (suite l)
								else exo3 c (suite l);;
let ex3=fun nom fichier -> exo3 nom (trans (lire fichier));;
ex3 "mpo" "donnees2.dat";;						

(* Exercice 4 *)
let max2 = fun (a,b) c -> if b > snd c then (a,b) else c;;
let rec maxi = function l -> if l=vide then failwith "impossible"
					else if (suite l) = vide then tete l
					else max2 (tete l) (maxi(suite l));;
let exo4 = function l -> fst( maxi l);;
let q4 = function fichier -> exo4 (trans(lire fichier));;
q4 "donnees2.dat";;