# Coverage related variables
COV_DIR		= coverage
GCOV_FLAGS	= -fprofile-arcs -ftest-coverage -fno-inline -O0 -g

# Coverage targets
.PHONY: coverage
coverage: CFLAGS += $(GCOV_FLAGS)
coverage: clean all $(TEST_NAME)
	@mkdir -p $(COV_DIR)
	@./$(TEST_NAME)
	@echo "Coverage data generated. Use 'make report_coverage' to see statistics."

.PHONY: report_coverage
report_coverage:
	@echo "Coverage statistics:"
	@mkdir -p $(COV_DIR)
	@find $(BUILD_DIR) -name "*.gcno" -exec gcov -b {} +
	@mv *.gcov $(COV_DIR)/
	@echo "Coverage report generated in $(COV_DIR) directory."
	@echo "Detailed report available on Codecov after pushing to the repository."

.PHONY: clean_coverage
clean_coverage:
	@rm -rf $(COV_DIR)
	@find $(BUILD_DIR) -name '*.gcno' -delete
	@find $(BUILD_DIR) -name '*.gcda' -delete
	@find . -name '*.gcov' -delete
