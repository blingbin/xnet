all:
	make -C ./common/
	make -C ./common/tests/


clean:
	make -C ./common/ clean
	make -C ./common/tests clean

.PHONY: all clean
