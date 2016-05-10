# -*- coding: utf-8 -*-
"""
Éditeur de Spyder

TP d'Outils Statistiques sur la régression linéaire.
"""

# TP REGRESSION LINEAIRE

import matplotlib.pyplot as plt

#Question 1

pays = {}
pays["Suisse"] = [4.0, 3432]
pays["France"] = [5.7, 3273]
pays["Suede"] = [4.9, 3049]
pays["USA"] = [3.0, 3642]
pays["Ex-URSS"] = [14.8, 3394]
pays["Chine"] = [69.6, 2628]
pays["Inde"] = [63.8, 2204]
pays["Bresil"] = [26.2, 2643]
pays["Perou"] = [38.3, 2192]
pays["Algerie"] = [24.7, 2687]
pays["Ex-Zaire"] = [65.7, 2459]

l = pays.keys()
lg = len(l)
pop_agricole = [] #X
calories = [] #Y

moy_pop_agricole = 0.0
moy_calories = 0.0

for i in range (lg) :
    pop_agricole.append(pays[l[i]][0])
    calories.append(pays[l[i]][1])
    
    moy_pop_agricole += pays[l[i]][0]
    moy_calories += pays[l[i]][1]

plt.plot(pop_agricole,calories)

moy_pop_agricole /= lg
moy_calories /= lg

#Question 2
ecart_pop_agricole_calories = 0.0
moy_ecart_pop_agricole = 0.0
moy_ecart_calories = 0.0

for i in range (lg) :
    ecart_pop_agricole_calories += (pop_agricole[i] - moy_pop_agricole) * (calories[i] - moy_calories)
    moy_ecart_pop_agricole += ((pop_agricole[i] - moy_pop_agricole) ** 2)
    moy_ecart_calories += ((calories[i] - moy_calories) ** 2)

beta1 = ecart_pop_agricole_calories / moy_ecart_pop_agricole
beta0 = moy_calories - beta1 * moy_pop_agricole

#Question 3
regression = []
for i in range (lg) :
    regression.append(beta0 + beta1 * pop_agricole[i])

plt.plot(pop_agricole, regression)

#Question 4
r = ecart_pop_agricole_calories / ((moy_ecart_pop_agricole ** 0.5) * (moy_ecart_calories ** 0.5))

print "r =", r

# r proche de -1 -> corrélation possible