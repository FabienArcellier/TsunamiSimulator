BIN=../bin
SRC=../src
OBJ=../obj
TESTS=../tests
INCLUDES=../includes

CC=gcc
CFLAGS=-Wall -pg `pkg-config --cflags gtk+-2.0` -I "$(INCLUDES)" -I "$(INCLUDES)/privates"
LDFLAGS=-Wall -pg `pkg-config --libs gtk+-2.0` `pkg-config --libs gmodule-2.0`
EXEC=main

all: $(BIN)/$(EXEC) copy_ui

test_cyril:$(BIN)/ground_area_builder_tests

tests: $(BIN)/angle_tests $(BIN)/event_tests $(BIN)/earthquake_event_tests $(BIN)/earthquake_event_spike $(BIN)/wave_propagation_event_tests $(BIN)/timeline_tests $(BIN)/propagation_timeline_processings_tests $(BIN)/wave_signal_tests $(BIN)/ground_tests $(BIN)/ground_neighbour_tests $(BIN)/ground_area_tests $(BIN)/ground_area_energy_map_tests $(BIN)/ground_view_spike $(BIN)/ground_area_text_storage_tests $(BIN)/earthquake_propagation_with_report_spike $(BIN)/earthquake_events_text_storage_tests tests_copy $(BIN)/earthquake_propagation_with_report_spike_with_map $(BIN)/ground_area_to_pixbuf_factory_tests $(BIN)/simulation_tests $(BIN)/simulation_text_storage_tests

#################################
#
#	Binaire
#
#################################

$(BIN)/main_console: $(OBJ)/angle.o $(OBJ)/file.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/earthquake_event.o $(OBJ)/ground_area_to_pixbuf_factory.o $(OBJ)/simulation.o $(OBJ)/simulation_text_storage.o $(OBJ)/earthquake_events_text_storage.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/Main_console.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/main: $(OBJ)/angle.o $(OBJ)/file.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/earthquake_event.o $(OBJ)/ground_area_to_pixbuf_factory.o $(OBJ)/simulation.o $(OBJ)/simulation_text_storage.o $(OBJ)/earthquake_events_text_storage.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/main.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_to_pixbuf_factory_tests: $(OBJ)/file.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/ground_area_to_pixbuf_factory.o $(OBJ)/ground_area_to_pixbuf_factory_tests.o $(OBJ)/ground_area_energy_map.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_text_storage_tests: $(OBJ)/file.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/ground_area_text_storage_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/simulation_text_storage_tests : $(OBJ)/angle.o $(OBJ)/file.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/earthquake_event.o $(OBJ)/ground_area_to_pixbuf_factory.o $(OBJ)/simulation.o $(OBJ)/simulation_text_storage.o $(OBJ)/simulation_text_storage_tests.o $(OBJ)/earthquake_events_text_storage.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/simulation_tests : $(OBJ)/angle.o $(OBJ)/file.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/earthquake_event.o $(OBJ)/ground_area_to_pixbuf_factory.o $(OBJ)/simulation.o $(OBJ)/simulation_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/earthquake_propagation_with_report_spike_with_map: $(OBJ)/angle.o $(OBJ)/file.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_text_storage.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/earthquake_event.o $(OBJ)/earthquake_propagation_with_report_spike_with_map.o $(OBJ)/ground_area_to_pixbuf_factory.o 
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/earthquake_propagation_with_report_spike: $(OBJ)/angle.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_text_storage.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/earthquake_event.o $(OBJ)/earthquake_propagation_with_report_spike.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_view_spike: $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_view_spike.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_energy_map_tests: $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_energy_map.o $(OBJ)/ground_area_energy_map_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_builder_tests: $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o  $(OBJ)/ground_area_builder.o $(OBJ)/ground_area_builder_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_area_tests: $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/ground_area_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_neighbour_tests: $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_neighbour_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/ground_tests: $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/wave_signal_tests: $(OBJ)/wave_signal.o $(OBJ)/wave_signal_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/propagation_timeline_processings_tests: $(OBJ)/angle.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/timeline.o $(OBJ)/wave_propagation_event.o $(OBJ)/propagation_timeline_processings.o $(OBJ)/propagation_timeline_processings_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/timeline_tests: $(OBJ)/event.o $(OBJ)/timeline.o  $(OBJ)/timeline_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/wave_propagation_event_tests: $(OBJ)/angle.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/wave_propagation_event.o $(OBJ)/wave_propagation_event_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/earthquake_event_spike: $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/earthquake_event.o $(OBJ)/timeline.o $(OBJ)/earthquake_event_spike.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/earthquake_events_text_storage_tests: $(OBJ)/file.o $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/earthquake_event.o $(OBJ)/earthquake_events_text_storage.o  $(OBJ)/earthquake_events_text_storage_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/earthquake_event_tests: $(OBJ)/event.o $(OBJ)/wave_signal.o $(OBJ)/ground.o $(OBJ)/ground_neighbour.o $(OBJ)/ground_area.o $(OBJ)/earthquake_event.o $(OBJ)/earthquake_event_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/event_tests: $(OBJ)/event.o $(OBJ)/event_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN)/angle_tests: $(OBJ)/angle.o $(OBJ)/angle_tests.o
	$(CC) $(LDFLAGS) -o $@ $^

#################################
#
#	Objets
#
#################################

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/Main_console.o : $(SRC)/Main_console.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/simulation_text_storage.o : $(SRC)/simulation_text_storage.c $(INCLUDES)/simulation_text_storage.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/simulation.o : $(SRC)/simulation.c $(INCLUDES)/simulation.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_energy_text_storage.o : $(SRC)/ground_area_energy_text_storage.c $(INCLUDES)/ground_area_energy_text_storage.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_to_pixbuf_factory.o : $(SRC)/ground_area_to_pixbuf_factory.c $(INCLUDES)/ground_area_to_pixbuf_factory.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_text_storage.o : $(SRC)/ground_area_text_storage.c $(INCLUDES)/ground_area_text_storage.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_energy_map.o : $(SRC)/ground_area_energy_map.c $(INCLUDES)/ground_area_energy_map.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_builder.o : $(SRC)/ground_area_builder.c $(INCLUDES)/ground_area_builder.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area.o : $(SRC)/ground_area.c $(INCLUDES)/ground_area.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_neighbour.o : $(SRC)/ground_neighbour.c $(INCLUDES)/ground_neighbour.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground.o : $(SRC)/ground.c $(INCLUDES)/ground.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/wave_signal.o : $(SRC)/wave_signal.c $(INCLUDES)/wave_signal.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/propagation_timeline_processings.o : $(SRC)/propagation_timeline_processings.c $(INCLUDES)/propagation_timeline_processings.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/timeline.o : $(SRC)/timeline.c $(INCLUDES)/timeline.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/wave_propagation_event.o : $(SRC)/wave_propagation_event.c $(INCLUDES)/wave_propagation_event.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_events_text_storage.o : $(SRC)/earthquake_events_text_storage.c $(INCLUDES)/earthquake_events_text_storage.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_event.o : $(SRC)/earthquake_event.c $(INCLUDES)/earthquake_event.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/event.o : $(SRC)/event.c $(INCLUDES)/event.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/file.o : $(SRC)/file.c $(INCLUDES)/file.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/angle.o : $(SRC)/angle.c $(INCLUDES)/angle.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/colored_pixbuf_factory.o: $(SRC)/colored_pixbuf_factory.c $(INCLUDES)/colored_pixbuf_factory.h
	$(CC) $(CFLAGS) -o $@ -c $<

#################################
#
#	Tests
#
#################################

$(OBJ)/ground_view_spike.o: $(TESTS)/ground_view_spike.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_to_pixbuf_factory_tests.o : $(TESTS)/ground_area_to_pixbuf_factory_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_text_storage_tests.o : $(TESTS)/ground_area_text_storage_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/simulation_text_storage_tests.o : $(TESTS)/simulation_text_storage_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/simulation_tests.o : $(TESTS)/simulation_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_energy_map_tests.o : $(TESTS)/ground_area_energy_map_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_builder_tests.o : $(TESTS)/ground_area_builder_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_area_tests.o : $(TESTS)/ground_area_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_neighbour_tests.o : $(TESTS)/ground_neighbour_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/ground_tests.o : $(TESTS)/ground_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/wave_signal_tests.o : $(TESTS)/wave_signal_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/propagation_timeline_processings_tests.o : $(TESTS)/propagation_timeline_processings_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/timeline_tests.o : $(TESTS)/timeline_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_event_spike.o : $(TESTS)/earthquake_event_spike.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/wave_propagation_event_tests.o : $(TESTS)/wave_propagation_event_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_propagation_with_report_spike_with_map.o : $(TESTS)/earthquake_propagation_with_report_spike_with_map.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_propagation_with_report_spike.o : $(TESTS)/earthquake_propagation_with_report_spike.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_events_text_storage_tests.o : $(TESTS)/earthquake_events_text_storage_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/earthquake_event_tests.o : $(TESTS)/earthquake_event_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/event_tests.o : $(TESTS)/event_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/angle_tests.o : $(TESTS)/angle_tests.c
	$(CC) $(CFLAGS) -o $@ -c $<

#################################
#
#	Utilitaires
#
#################################

tests_copy:
	-cp test.sh $(BIN)/test.sh

copy_ui:
	cp $(SRC)/ui/main.glade $(BIN)/ui/main.glade
	cp $(SRC)/ui/calculate.glade $(BIN)/ui/calculate.glade
	cp $(SRC)/ui/simulate.glade $(BIN)/ui/simulate.glade

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