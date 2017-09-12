#### Pra quem interessar

Código importado de um repositório antes-privado do Bitbucket, para a aula de Computação Gráfica do primeiro semestre de 2013 no Instituto de Ciências e Tecnologia da Universidade Federal de São Paulo.

É um código feito na faculdade. Não espere nada além disso. No mais, resto do leia-me a seguir.

# BATALHA MEDIEVAL
NÃO É MAIS VELHO-OESTE

# Como clonar esse repositório
[https://confluence.atlassian.com/pages/viewpage.action?pageId=270827678]  
Siga os passos 2, 3, 4 e 6 do link, depois execute na linha de comando:  

	git clone git@bitbucket.org:Hueho/medieval-cg.git

Uma pasta mágica chamada medieval-cg deverá se materializar.

# Não sei usar o Git!!!11!

Leia: [http://git-scm.com/documentation]

# Como compilar

Abra a pasta no terminal, use o comando "make" para compilar, "make clean" para recompilar do zero.

# Que pastas são essas?

***src/***: colocaremos o código-fonte aqui  
***resources/***: colocaremos texturas, imagens e o escambau aqui  
***bin/***: aqui vai ficar o executável depois de compilado  

# Que "Makefile" é esse?

Um arquivo pro programa "make" utilizar que fala quais arquivos devem ser compilados e linkados, e que torna nossa vida mais feliz se a gente quiser fazer o programa usando mais do que um arquivo em C

# Porquê não esperou a gente?

Porque sou afobado.

# Que "README.md" é esse?

O "leia-me" que você está lendo, em formato bruto de Markdown. Sintaxe é uma porcaria (mas o Gedit tem suporte nativo pelo menos). Detalhes de como escrever aqui: [http://daringfireball.net/projects/markdown/]

# Comandos do Git

git branch: lista todas as branchs locais.  
git branch <nome>: cria uma branch local com o nome passado.  
git checkout <nome>: muda para a branch com o nome passado.  
git pull: pega os últimos commits do master.  
git add . : adiciona todas as mudanças ao commit, tirando arquivos deletados.  
git add -u: adiciona mudanças que deletam arquivos.  
git commit: faz um commit.  
git rebase -i master: faz rebase interativo com base na branch master.  
git mergetool: se um rebase falhar, use para fazer o merge de cada arquivo com conflito.  
git rebase --continue: depois do merge dar certo, use para prosseguir com o rebase anterior.  
git rebase --abort: se quiser desistir do rebase, use para abortar.  
git push: manda os commits feitos pro master remoto (i.e o repositório)
	
# Licença
```
The MIT License (MIT)

Copyright (c) 2013-2017 Daniel Gracia, Aruã Mello, Kim Tostes, Rafael Januzzi

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
