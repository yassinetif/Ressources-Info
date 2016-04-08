(* DURAN Alizee - TP5 *)

(* Types *)
type terme = po|pf|op of string|entier of int;;
type 'a arbre = V | N of ('a * 'a arbre * 'a arbre);;
type 'a liste = vide | cons of  'a* 'a liste;;

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

let is_sepu = function `+`|`-`|`*`|`/`|`(`|`)` -> true
				| _ -> false;;

let rec saute_terme = function vide -> vide
        | cons(car,reste) as l -> if is_sep car or is_sepu car then l
                  else saute_terme reste;;

let char2str = function car -> make_string 1 car;;

let rec premier_terme = function vide -> ""
     | cons(car,reste) -> if is_sep car or is_sepu car then ""
                else char2str car ^  premier_terme reste;;

let rec analyselex = function vide->vide
  |cons (car,reste) as l -> if is_sep car then
            analyselex reste
    else if is_sepu car then cons(char2str car, analyselex reste)
    else cons(premier_terme l , analyselex (saute_terme l));;

let tout= function nom -> analyselex(lire_car nom);; 


(* Exercice 1 *)
let ch2term = function ("+"|"-"|"*"|"/") as ope -> op ope
						| v -> entier (int_of_string v);;

let rec trans = fun f vide -> vide
					| f (cons(tete, reste)) -> cons ((f tete), (trans f reste));;

let ma_liste = trans ch2term (analyselex (lire_car "exprinv.txt"));;

let op2fun = function op "+" -> prefix +
					| op "-" -> prefix -
					| op "/" -> prefix /
					| op "*" -> prefix *
					| _ -> failwith "impossible";;

let rec calculer = fun vide (cons(v, vide)) -> v
					| (cons(entier v,reste)) l -> calculer reste (cons(v,l))
					| (cons((op ope),reste)) (cons(v2,cons(v1,reste2))) -> calculer reste (cons((op2fun (op ope) v1 v2),reste2))
					| _ _ -> failwith "erreur de calcul";;

calculer ma_liste vide;;


(* Exercice 2 *)
let rec post2abis = fun vide (cons (a,vide)) -> a
							| (cons(entier v, reste)) l -> post2abis reste (cons(N(entier v, V,V),l))
							| (cons(op ope, reste)) (cons(a2,cons(a1, reste2))) -> post2abis reste (cons(N(op ope, a1, a2),reste2)) 
							| _ _ -> failwith "erreur";;

let post2a = function l -> post2abis l vide;;

post2a(ma_liste);;

