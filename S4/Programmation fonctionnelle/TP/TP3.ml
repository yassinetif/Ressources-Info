(* DURAN Alizee - TP3 *)

(* Contenu de lexical.ml *)
let lire_car =function nom ->
 let canal=open_in nom in
  let rec lirea =function () -> 
         try let a = input_char canal in 
            cons(a ,lirea ()) with
       End_of_file -> begin close_in canal;vide end
      in  lirea ();;

let is_sep = function ` `| `\n` -> true
                     | _ -> false;;


let rec saute_mot = function vide -> vide
        | cons(car,reste) as l -> if is_sep car then l
                  else saute_mot reste;;

let char2str = function car -> make_string 1 car;;

let rec  premier_mot = function vide -> ""
     | cons(car,reste) -> if is_sep car then ""
                else char2str car ^  premier_mot reste;;

let rec analyselex = function vide->vide
  |cons (car,reste) as l -> if is_sep car then
            analyselex reste
    else cons(premier_mot l , analyselex (saute_mot l));;


let tout= function nom -> analyselex(lire_car nom);; 

(* Exercice - Trouver le mot le plus utilise dans un texte *)

let plus1 = function (a,b) -> (a,b+1);;
let rec repete = fun m l -> if l=vide then cons((m,1), vide)
							else if m < fst (tete l) then cons((m,1),l)
							else if m > fst (tete l) then cons(tete l, repete m (suite l))
							else cons(plus1(tete l), suite l);;
let rec tri = function l -> if l=vide then vide
							else repete (tete l) (tri (suite l));;

let max2 = fun (a,b) c -> if b > snd c then (a,b) else c;;
let rec maxi = function l -> if l=vide then failwith "impossible"
								else if (suite l) = vide then tete l
								else max2 (tete l) (maxi(suite l));;
let exercice = function l -> fst(maxi l);;

exercice(tri(tout "C:/Users/spi2110/Desktop/libe.txt"));;




