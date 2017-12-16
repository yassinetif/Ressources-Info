;DURAN Alizée

(deffacts faits-initiaux
	(output "Bonjour, comment je peux vous aider ? "))

(defrule interaction    
	?fact <- (output $?prop)
	=>
	(retract ?fact)
	(printout t "ELIZA> " ?prop crlf "> ")
	(bind ?var (explode$ (readline)))
	;(lowcase ?var) 					;Problème avec la transformation en minuscules
	(assert (input ?var)))

(defrule regle-salutation
	?fact <- (input $? comment ca va $?)
	=>
	(retract ?fact)
	(assert (output "Ca va bien, merci")))

(defrule regle-aurevoir
	?fact <- (input $? au revoir $?)
	=>
	(retract ?fact)
	(printout t "ELIZA> A bientot pour une prochaine fois !" crlf)
	(halt))

;(defrule regle-apprendre-moche
;	(input $?)
;	=>
;	(assert (output "Merci de l'info!")))

(defrule regle-apprendre
	?fact <- (input un|une|le|la $?mot est un|une|le|la $?valeur)
	=>
	(retract ?fact)
	(assert (relation ?mot ?valeur))
	(assert (output "Merci de l'info!" )))

(defrule regle-cest-quoi
	;(declare (salience 10))
	?fact <- (input c'est quoi un|une|le|la ?mot)
	(relation ?mot $?valeur)
	=>
	(retract ?fact)
	(assert (output un ?mot est un ?valeur je crois)))

(defrule regle-je-sais-pas
	(declare (salience -1))
	?fact <- (input $? c'est quoi un $?mot)
	(not (relation $?mot $?valeur))
	=>
	(retract ?fact)
	(assert (output je suis incapable de vous dire ce que c'est un ?mot)))

(defrule regle-comprendre
	(declare (salience -2))
	?fact <- (input $?)
	=>
	(retract ?fact)
	(assert (output "raconte moi davantage")))