;DURAN Alizée

(deffacts faits-initiaux
        (est-poilu A1)
        (a-poche-ventrale A1)
        (fait-grand-bond A1)

        (est-poilu A2)
        (a-poche-ventrale A2)
        (grimpe-arbres A2)

        (est-poilu A3)
        (est-carnivore A3)
        (vole A3)

        (est-poilu A4)
        (est-carnivore A4)       
        (pond-oeufs A4)

        (mange-eucalyptus A5)
        (mange-bambou A5))

;Règles

(defrule donne-lait
	(est-poilu ?x)
	=>
	(assert (donne-lait ?x)))

(defrule provient-hs
        (est-marsupial ?x)
        =>
        (assert (provient-hs ?x)))

(defrule est-phalanger
	(a-poche-ventrale ?x)
	(a-longues-phalanges ?x)
	=>
	(assert (est-phalanger ?x)))

(defrule est-koala
	(est-marsupial ?x)
	(grimpe-arbres ?x)
	=>
	(assert (est-koala ?x)))

(defrule est-marsupial
	(donne-lait ?x)
	(a-poche-ventrale ?x)
	=>
	(assert (est-marsupial ?x)))

(defrule est-kangourou
        (est-marsupial ?x)
        (fait-grand-bond ?x)
        =>
        (assert (est-kangourou ?x)))

(defrule est-mammifere
        (donne-lait ?x)
        =>
        (assert (est-mammifere ?x)))

(defrule est-koala
        (mange-eucalyptus ?x)
        =>
        (assert(est-koala ?x)))

(defrule est-chauve-souris
        (vole ?x)
        (est-carnivore ?x)
        (donne-lait ?x)
        =>
        (assert (est-chauve-souris ?x)))

(defrule est-faucon
        (est-oiseau ?x)
        (est-carnivore ?x)
        =>
        (assert (est-faucon ?x)))

(defrule est-opposum
        (est-marsupial ?x)
        (est-carnivore ?x)
        (a-queue-prehensile ?x)
        =>
        (assert (est-opposum ?x)))

(defrule est-oiseau
        (vole ?x)
        (pond-oeufs ?x)
        =>
        (assert (est-oiseau ?x)))

(defrule est-ornithorynque
        (est-mammifere ?x)
        (pond-oeufs ?x)
        =>
        (assert (est-ornithorynque ?x)))

; Recherche des animaux

(defrule animal1 "Un animal poilu, à poche ventrale, et qui fait des grands bonds"
        (est-poilu ?x)
        (a-poche-ventrale ?x)
        (fait-grand-bond ?x)
        =>
        (printout t ?x " est un kangourou" crlf ))

;Problème d'affichage du koala dans la base de faits mais présente toutes les caractéristiques pour en être un
(defrule animal2 "Un animal poilu, à poche ventrale, et qui grimpe aux arbres"
        (est-poilu ?x)
        (a-poche-ventrale ?x)
        (grimpe-arbres ?x)
        =>
        (printout t ?x " est un koala " crlf ))

(defrule animal3 "Un animal poilu, carnivore, et qui vole"
        (est-poilu ?x)
        (est-carnivore ?x)
        (vole ?x)
        =>
        (printout t ?x " est une chauve-souris " crlf ))

;Problème avec la recherche de l'animal 4: règle présente dans la base de faits mais n'affiche pas la phrase lorsque la ligne est décommentée
(defrule animal4 "Un animal poilu, carnivore, et qui pond des œufs"
        (est-poilu ?x)
        ;(carnivore ?x) 
        (pond-oeufs ?x)
        =>
        (printout t ?x " est un ornithorynque " crlf))

;Aucun animal ne présente ces deux caractéristiques donc pas d'affichage sur le terminal
(defrule animal5 "Un animal qui mange des feuilles d’eucalyptus et des pousses de bambou"
        (mange-eucalyptus ?x)
        (regime-unique ?x)
        =>
        (printout t ?x " est un animal qui mange des feuilles d'eucalyptus et des pousses de bambou" crlf ))