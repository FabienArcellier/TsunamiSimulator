BIN=../bin
SRC=../src
OBJ=../obj
TESTS=../tests
INCLUDES=../includes

CC=gcc
CFLAGS=-Wall `pkg-config --cflags gtk+-2.0` -I "$(INCLUDES)" -I "$(INCLUDES)/privates"
LDFLAGS=-Wall `pkg-config --libs gtk+-2.0` `pkg-config --libs gmodule-2.0`
EXEC=rendering_water

all: $(BIN)/$(EXEC)

tests: $(BIN)/water_hmap_tests $(BIN)/ground_tests $(BIN)/ground_area_tests $(BIN)/ground_area_text_storage_tests $(BIN)/water_hmap_csv_storage_tests $(BIN)/water_simulation_spike_n_iterations $(BIN)/point_water_transformation_tests

#################################
#
#	Binaire
#
#################################

$(BIN)/rendering_water: $(OBJ)/water_hmap.o $(OBJ)/water_simulation_engine.o $(OBJ)/water_rendering_engine.o $(OBJ)/point_water_transformation.o $(OBJ)/colored_pixbuf_factory.o $(OBJ)/ui/main_ui.o $(OBJ)/ui/main_builder.o $(OBJ)/main.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/point_water_transformation_tests: $(OBJ)/water_hmap.o $(OBJ)/water_simulation_engine.o $(OBJ)/point_water_transformation.o $(OBJ)/point_water_transformation_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/water_simulation_spike_n_iterations: $(OBJ)/water_hmap.o $(OBJ)/water_hmap_csv_storage.o $(OBJ)/water_simulation_engine.o $(OBJ)/water_simulation_spike_n_iterations.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/water_hmap_csv_storage_tests: $(OBJ)/water_hmap.o $(OBJ)/water_hmap_csv_storage.o $(OBJ)/water_hmap_csv_storage_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_text_storage_tests: $(OBJ)/ground.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/ground_area_text_storage_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_tests: $(OBJ)/ground.o $(OBJ)/ground_area.o $(OBJ)/ground_area_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_tests: $(OBJ)/ground.o $(OBJ)/ground_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/water_hmap_tests: $(OBJ)/water_hmap.o $(OBJ)/water_hmap_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

#################################
#
#	Objets
#
#################################

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ui/main_builder.o : $(SRC)/ui/main_builder.c $(INCLUDES)/ui/main_builder.h
	cp "$(SRC)/ui/main.glade" "$(BIN)/ui/main.glade"
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ui/main_ui.o : $(SRC)/ui/main_ui.c $(INCLUDES)/ui/main_ui.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/water_rendering_engine.o: $(SRC)/water_rendering_engine.c $(INCLUDES)/water_rendering_engine.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/point_water_transformation.o: $(SRC)/point_water_transformation.c $(INCLUDES)/point_water_transformation.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/water_simulation_engine.o: $(SRC)/water_simulation_engine.c $(INCLUDES)/water_simulation_engine.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/water_hmap_csv_storage.o: $(SRC)/water_hmap_csv_storage.c $(INCLUDES)/water_hmap_csv_storage.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/water_hmap.o: $(SRC)/water_hmap.c $(INCLUDES)/water_hmap.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_text_storage.o : $(SRC)/ground_area_text_storage.c $(INCLUDES)/ground_area_text_storage.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area.o : $(SRC)/ground_area.c $(INCLUDES)/ground_area.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground.o : $(SRC)/ground.c $(INCLUDES)/ground.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/colored_pixbuf_factory.o: $(SRC)/colored_pixbuf_factory.c $(INCLUDES)/colored_pixbuf_factory.h
	$(CC) $(CFLAGS) -o $@ -c $<

#################################
#
#	Tests
#
#################################

$(OBJ)/water_simulation_spike_n_iterations.o: $(TESTS)/water_simulation_spike_n_iterations.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/point_water_transformation_tests.o: $(TESTS)/point_water_transformation_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/water_hmap_csv_storage_tests.o: $(TESTS)/water_hmap_csv_storage_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/water_hmap_tests.o: $(TESTS)/water_hmap_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_text_storage_tests.o : $(TESTS)/ground_area_text_storage_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_tests.o : $(TESTS)/ground_area_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_tests.o : $(TESTS)/ground_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

#################################
#
#	Utilitaires
#
#################################

init : clean_all
	-mkdir $(BIN)
	-mkdir $(BIN)/ui
	-mkdir $(OBJ)
	-mkdir $(OBJ)/ui

clean:
	-rm $(OBJ)/*.o
	-rm $(OBJ)/ui/*.o

clean_all: clean
	-rm $(BIN)/$(EXEC)
	-rm $(BIN)/ui/main.glade