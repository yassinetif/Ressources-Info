(* DURAN	Alizee *)
(* Fonction somme *)
let fonction = function a -> function b -> a+b;;
(* Quelques fonctions de test *)
let f10 = function truc -> (truc 2.0) -. 3.0;;
let f11 = function f -> int_of_float (f 0);;

(* Fonctions maximum*)
let maximum = function (a,b) -> if (a>b) then a else b;;
let max3 = fun a b c -> maximum(maximum(a,b),c);;

(* Determine le predecesseur d'un nombre donne*)
pred 5;;

(* Fonction som sans utiliser le signe + *)
let rec som = function (a,b) -> if a>0 then som(pred a, succ b)
								else  b;;
som(6,2);;

(* Version terminale - Fonction prod sans utiliser le signe * *)			
let rec prodt = function (a, b, res) -> if a > 0 then prodt(pred a, b, res+b) 
										else res;;
prodt(3,6,0);;

(* Utilisation de as - Fonction qui associe a tout couple a,b € N un autre couple tel que c.d=0 et a+d=c+b *)									
let rec couple = function(a,b) as c -> if a=0 or b=0 then c
										else couple(pred a, pred b);;
couple(6,2);;
(* Fonction puissance *)
let rec puissance = function (n, x) -> if n>0 then x*puissance((n-1), x)
										else 1;;
puissance(3,5);;										

(* 2e version de puissance *)								
let rec puiss2 = function (x,n) -> if n mod 2=0 then puiss2(x*x, n/2)
									else if n=0 then 1
									else x * puiss2(x*x, n/2);;

(* Fonction produit de produits *)
let rec produit = function(n,f) ->  if n=0 then f 0.0
									else (f (float_of_int n)) *. produit(n-1,f);;
let prod30 = function x -> 2.0 *.(cos x);;
produit(30, prod30);;

(* Version terminale - Fonction produit de produits *)
let rec prodterm = function (n,f,res) -> if n=0 then res*. f 0.0
											else prodterm(n-1, f, res*.f(float_of_int n));;
let prodterm15 = function x-> 2.0*.sin(x+.3.) ;;
prodterm(15, prodterm15,1.0);;

(* Fonction somme de somme *)
let rec somme = function (n,f) -> if n=0 then f 0 else f(n*n) +. somme(n-1,f);;
let somme30 = function i -> 2.0*.sin(float_of_int i);;
somme(30, somme30);;

(* Fonction qui calcule la somme des carres constituant un nbr dans sa representation en base 10 *)
let rec suiv = function n -> if n=0 then 0
								else suiv(n/10) + (n mod 10)*(n mod 10);;
suiv 456;;
1;;