# Latex Style for Student Theses

The latex document class for student theses at the MTS. 

## Installation

There are many ways to include this package in your Latex Installation. Below are listed some examples. Further examples can be found [here](https://www.google.com/search?q=latex+manually+install+package).

### MikTex
see [MikTex](https://tex.stackexchange.com/questions/2063/how-can-i-manually-install-a-package-on-miktex-windows?noredirect=1&lq=1)

### TexLive
Find out your TEXMFHOME directory by running
```
tlmgr conf | findstr "TEXMFHOME"
```
and if necessary create a TDS-compliant directory below TEXMFHOME
```
cd "output_of_previous_cmd"
mkdir tex\latex
cd tex\latex
```
Now you can either clone the repository
```
git clone https://gitlab.rhrk.uni-kl.de/mts/studentische-arbeiten-vorlage-latex.git
```
or download an archive and extract the files into that directory

## Example
After installing the package you can start from this [minimal example](https://gitlab.rhrk.uni-kl.de/mts/studentische-arbeiten-vorlage-latex/-/wikis/Minimal-Example). 

A brief description of the class options are found [here](https://gitlab.rhrk.uni-kl.de/mts/studentische-arbeiten-vorlage-latex/-/wikis/Class-Options).

