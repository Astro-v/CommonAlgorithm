# Common Algorithm

## Introduction

> Ce répertoire gitlab a pour objectif de référencé les différentes structures algorithmiques de base en C++.
> On s'intéresse dans un premiers temps aux Design pattern en C++ modern. Ces pattern sont issus du cours de Dmitri Nesteruk sur Udemy.

## Design Pattern


> Il existe 3 types de design pattern :


> | Creational | Structural | Behavioral             |
> | ---------- | ---------- | ---------------------- |
> | Builder    | Adapter    | Chain of resposibility |
> | Factories  | Bridge     | Command                |
> | Prototype  | Composite  | Interpreter            |
> | Singleton  | Decorator  | Iterator               |
> |            | Facade     | Mediator               |
> |            | Flyweight  | Memento                |
> |            | Proxy      | Observer               |
> |            |            | State                  |
> |            |            | Strategy/Policy        |
> |            |            | Template method        |
> |            |            | Visitor                |


### Creational

#### Builder

```
Le design pattern **builder** est utile lorsqu'on souhaite créer un objet de façon incrémentale.

*Exemple : Pour construire du code html, on peut le créer de façon incrémental en ajoutant récurcivement des balises enfants aux balises parents*
```

#### Factories

```
**Problem it solve :** Il n'est parfois pas possible de surcharger le constructeur. *Pour un point, il peut être définit avec des coordonné polaire ou carthesienne*

Le design pattern **factory** peut prendre différentes formes :

**Factory method :** Dans chaque classe, on a un methode new_xxx pour créer un objet. *Pour un point ce serait new_polar ou new_carthesian*

**Factory :** Une classe à part entière contenant des méthodes pour construire des objets.

**Inner factory :** Une classe à part entière contenant des méthodes pour construire des objets à l'intérieur de la classe.

**Abstract factory :** Une classe abstraite pour construire une classe dont herite les différentes factory spécifique. 

*Exemple : Coffee et Tea herite de HotDrink*
*CoffeeFactory et TeaFactory herite de HotDrinkFactory, ils permetent de créer des Tea et des Coffee avec des volumes quelconques.*
*DrinkFactory permet de créer des Tea et des Coffee avec des volumes pré-définis*
```

#### Prototype

```
Le **prototype** consiste à créer un nouvel objet à partir d'une base déjà établie. *La classe contact stock les nom, prenom et l'adresse, un prototype consite par exemple à créer une adresse générique et de pouvoir enregistrer les contacts sans avoir à saisir à nouveau les adresse*
```

#### Singleton

### Structural

### Behavioral
