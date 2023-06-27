all: anitaborg_donations test_treemap

test_treemap: test_treemap.cc treemap.h
	g++ -Wall -Werror -std=c++11 -o $@ $< -lgtest -pthread

anitaborg_donations: anitaborg_donations.cc treemap.h
	g++ -Wall -Werror -std=c++11 -o $@ $<

.PHONY: tree_lint
tree_lint:
	./cpplint treemap.h

.PHONY: anitaborg_dotations_cleanupcrew_lint
anitaborg_dotations_cleanupcrew_lint:
	./cpplint anitaborg_donations.cc

.PHONY: clean 
clean:
	rm -f test_treemap anitaborg_donations *.dat
