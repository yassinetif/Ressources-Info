byCar(auckland,hamilton).
byCar(hamilton,raglan).
byCar(valmont,saarbruecken).
byCar(valmont,metz).

byTrain(metz,frankfurt).
byTrain(saarbruecken,frankfurt).
byTrain(metz,paris).
byTrain(saarbruecken,paris).

byPlane(frankfurt,bangkok).
byPlane(frankfurt,singapore).
byPlane(paris,losAngeles).
byPlane(bangkok,auckland).
byPlane(singapore,auckland).
byPlane(losAngeles,auckland).

% a)
voyage(X,Y) :- byCar(X,Y).
voyage(X,Y) :- byTrain(X,Y).
voyage(X,Y) :- byPlane(X,Y).
voyage(X,Y) :- byCar(X,Z), voyage(Z,Y).
voyage(X,Y) :- byTrain(X,Z), voyage(Z,Y).
voyage(X,Y) :- byPlane(X,Z), voyage(Z,Y).

% b)
/*
travel(X,Y,[go(X,Y)]) :- byCar(X,Y).
travel(X,Y,[go(X,Y)]) :- byTrain(X,Y).
travel(X,Y,[go(X,Y)]) :- byPlane(X,Y).
travel(X,Y,[go(X,Z)|T]) :- byCar(X,Z), travel(Z,Y,T).
travel(X,Y,[go(X,Z)|T]) :- byTrain(X,Z), travel(Z,Y,T).
travel(X,Y,[go(X,Z)|T]) :- byPlane(X,Z), travel(Z,Y,T).
*/

% c)
travel(X,Y,[goByCar(X,Y)]) :- byCar(X,Y).
travel(X,Y,[goByTrain(X,Y)]) :- byTrain(X,Y).
travel(X,Y,[goByPlane(X,Y)]) :- byPlane(X,Y).
travel(X,Y,[goByCar(X,Z)|T]) :- byCar(X,Z), travel(Z,Y,T).
travel(X,Y,[goByTrain(X,Z)|T]) :- byTrain(X,Z), travel(Z,Y,T).
travel(X,Y,[goByPlane(X,Z)|T]) :- byPlane(X,Z), travel(Z,Y,T).