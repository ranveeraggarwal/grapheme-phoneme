.PHONY: prepare filter compile accuracy clean
FOLD=5
all: clean prepare filter compile accuracy

prepare:
	@mkdir -p bin
	@mkdir -p temp

filter:
	@echo "Filtering graphenes and phonemes of equal length.."
	@python ./src/get_equal_graphene_phoneme.py
	@echo "Filtering done"

compile:
	@echo "compiling source code"
	@g++ ./src/phoneme_to_graphene.cpp -o ./bin/phoneme_to_graphene.out
	@echo "compilation done"

accuracy: src/k_fold_validation_accuracy.py
	@echo "Finding accuracy for $(FOLD)-fold validation..."
	@python ./src/k_fold_validation_accuracy.py -k $(FOLD)

clean:
	@echo "Cleaning project"
	@rm -rf bin/ temp/ src/*.pyc *.dat
	@echo "cleaned"

festival:
	@python src/festival.py