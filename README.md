# Jednoduchý spreadsheet

Vytvořte aplikaci implementující jednoduchý tabulkový editor.

Buňky pro váš spreadsheet musí podporovat

* literály (čísla, řetězce, ...)
* základní operátory: +, -, *, /
* alespoň 4 jednoduché funkce: sin, abs, concat, ...
* odkaz na jinou buňku: = A2 + abs(B1)

Buňky musí upravovat svůj obsah na základě změn odkazovaných buněk.

Buňka musí detekovat cykly a nesmí dovolit vytvořit výraz, který by cyklus způsobil.

Vytvořená tabulka musí jít uložit do souboru a opětovně zase načíst. Navrhněte vhodnou reprezentaci.

Buňky dále musí implementovat alespoň 1 z těchto funkcionalit:
* zpracovávat výrazy se závorkami
* agregační funkce přes sloupce, řádky a oblasti: avg(A2:A8), max(B1:C10)
* vykreslení grafu přes sloupce, řádky nebo oblasti

Použití polymorfismu (doporučeně):
* typy buněk: číslo, řetězec, výraz, funkce, ...
* grafické rozhraní: konzole, ncurses, SDL, OpenGL, ...
* různé druhy grafů