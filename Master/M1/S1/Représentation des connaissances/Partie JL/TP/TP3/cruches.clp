;DURAN Alizée
; Liste de cas d'erreurs sur clips lors du load : http://galahad.plg.inf.uc3m.es/~iat/CLIPS_REFERENCIA/Appendix_G_-_CLIPS_Error_Messages.html
; Incomplet car le programme ne trouve pas de réponse à la question et n'affiche donc pas la réponse

(deftemplate noeud
        (slot cruche3 (type INTEGER) (default 0) (range 0 3))
        (slot cruche4 (type INTEGER) (default 0) (range 0 4))
        (slot parent (type FACT-ADDRESS SYMBOL) (default nil))
        (slot action (type STRING) (default "Situation initiale -> ")))

(deffacts faits-initiaux
        (noeud))



;Règles pour remplir, vider et transvaser les cruches de 3 et 4 litres
(defrule remplir-cruche-3 "Remplir la cruche de 3 litres"
        ?fait <- (noeud (cruche3 ?x))
        (test (< ?x 3))
        =>
        (duplicate ?fait (cruche3 3) (parent ?fait) (action "Remplir la cruche de 3 litres -> ")))

(defrule remplir-cruche-4 "Remplir la cruche de 4 litres"
        ?fait <- (noeud (cruche4 ?y))
        (test (< ?y 4))
        =>
        (duplicate ?fait (cruche4 4) (parent ?fait) (action "Remplir la cruche de 4 litres -> ")))

(defrule vider-cruche-3 "Vider la cruche de 3 litres"
        ?fait <- (noeud (cruche3 ?x))
        =>
        (duplicate ?fait (cruche3 0) (parent ?fait) (action "Vider la cruche de 3 litres -> ")))

(defrule vider-cruche-4 "Vider la cruche de 4 litres"
        ?fait <- (noeud (cruche4 ?y))
        =>
        (duplicate ?fait (cruche4 0) (parent ?fait) (action "Vider la cruche de 4 litres -> ")))

(defrule transvaser-cruche-3 "Transvaser la cruche de 3 litres dans la cruche de 4 litres"
        ?fait <- (noeud (cruche3 ?x) (cruche4 ?y))
        (test (< ?y 4))
        =>
        (duplicate ?fait (cruche3 = (min 0 (+ ?x ?y))) (cruche4 = (max 4 (- ?x ?y))) (parent ?fait) (action "Transvaser la cruche de 3 litres dans la cruche de 4 litres -> ")))

(defrule transvaser-cruche-4 "Transvaser la cruche de 4 litres dans la cruche de 3 litres"
        ?fait <- (noeud (cruche3 ?x) (cruche4 ?y))
        (test (< ?x 3))
        =>
        (duplicate ?fait (cruche3 = (max 3 (- ?y ?x))) (cruche4 = (min 0 (+ ?y ?x))) (parent ?fait) (action "Transvaser la cruche de 4 litres dans la cruche de 3 litres -> ")))



;Affichage de la solution
(deffunction afficher-solution (?noeud) 
        (if (neq ?noeud nil) then
                (bind ?parent (fact-slot-value ?noeud parent)) 
                (bind ?action (fact-slot-value ?noeud action))
                (bind ?c3 (fact-slot-value ?noeud cruche3))
                (bind ?c4 (fact-slot-value ?noeud cruche4))
                (afficher-solution ?parent) 
                (printout t ?action "(" ?c3 " " ?c4 ")" crlf)))

(defrule deja-vu "Effacer les doublons"
        (declare (salience 100)) 
        ?f1 <- (noeud (cruche3 ?x) (cruche4 ?y))
        ?f2 <- (noeud (cruche3 ?x) (cruche4 ?y))
        (test (> (fact-index ?f2) (fact-index ?f1))) 
        => 
        (retract ?f2))

(defrule trouve "Eureka!"
        (declare (salience 100))
        ?final <- (noeud (cruche3 ?x) (cruche4 ?y))
        (test (or (= ?x 2) (= ?y 2)))
        =>
        (afficher-solution ?final)
        (halt))
