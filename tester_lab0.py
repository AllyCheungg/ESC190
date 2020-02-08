# tester script for ESC190 lab 0
from ESC190.lab0 import lab0
from ESC190.lab0.lab0 import BalancingTree
from ESC190.lab0.lab0_utilities import *


def test_languages(fname):
	data = open(fname, 'r')
	print("Testing tree building")
	languages = lab0.Languages()
	data_by_year = languages.build_trees_from_file(data)
	data.close()

	print(data_by_year)

	query = 'French'
	data_by_name = languages.query_by_name(query)
	
	print("The statistics for English in Canada, by year:")
	print(data_by_name)

	count = 1000000
	data_by_count = languages.query_by_count(count)

	print(data_by_count)

	return data_by_year


if __name__ == "__main__":
	ca_data_fname = 'data/ca_languages.csv'
	us_data_fname = ''
	ca_data_by_year = test_languages(ca_data_fname)



