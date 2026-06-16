nom_programme_generateur_aleatoire = Programme_generation_aleatoire_C/generateur_aleatoire
nom_programme_percolation = Programme_generation_aleatoire_C/percolation
nom_programme_marche_aleatoire = Marche_aleatoire/marche_aleatoire
nom_programme_test_densiter = Programme_test_statistique/test_densite

flag_percolation = -IProgramme_generation_aleatoire_C Compilation/libgeneration_aleatoire.a -lm
flag_marche_aleatoire= -IProgramme_generation_aleatoire_C Compilation/libgeneration_aleatoire.a -L/opt/local/lib -Llibs/ -lraylib -lm
flag_test_densiter= -IProgramme_generation_aleatoire_C Compilation/libgeneration_aleatoire.a -L/opt/local/lib -Llibs/ -lm


built_generation_aleatoire:
	gcc -c $(nom_programme_generateur_aleatoire).c -o Compilation/generateur_aleatoire.o
	ar rcs Compilation/libgeneration_aleatoire.a Compilation/generateur_aleatoire.o
	rm Compilation/generateur_aleatoire.o

run_percolation: built_generation_aleatoire
	gcc $(nom_programme_percolation).c $(flag_percolation) -o Compilation/percolation
	./Compilation/percolation
	rm Compilation/percolation

run_marche_aleatoire: built_generation_aleatoire
	gcc $(nom_programme_marche_aleatoire).c $(flag_marche_aleatoire) -o Compilation/marche_aleatoire
	./Compilation/marche_aleatoire
	rm Compilation/marche_aleatoire

run_test_densite: built_generation_aleatoire
	gcc $(nom_programme_test_densiter).c $(flag_test_densiter) -o Compilation/test_densite
	./Compilation/test_densite
	rm Compilation/test_densite

clean:
	rm -rf Compilation/*

presentation_total:
	pdflatex -output-directory=Compilation Presentation/annexe.tex
	pdflatex -output-directory=Compilation Presentation/annexe.tex
	pdflatex -output-directory=Compilation Presentation/presentation.tex

presentation:
	pdflatex -output-directory=Compilation Presentation/presentation.tex
	
teml:
	rm Compilation/presentation.aux
	rm Compilation/presentation.log
	rm Compilation/presentation.toc
	rm Compilation/presentation.snm
	rm Compilation/presentation.out
	rm Compilation/presentation.nav



