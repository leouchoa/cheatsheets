package main

import (
	"encoding/json"
	"fmt"
	"go_sqlite/internal/models"
	"log"
	"net/http"
	"strconv"
	"time"
)

func (a *application) home(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello World! %s", time.Now())
}

func (a *application) getBook(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil || id < 1 {
		http.NotFound(w, r)
		return
	}

	res, err := a.booksDB.SelectBook(id)

	if err != nil {
		// TODO: improve error handling
		log.Fatal(err)
	}

	fmt.Fprintf(
		w,
		"Queried data with id %d. Results: \nAuthor: %s\nName: %s\nIsdn: %d",
		id, res.Author, res.Name, res.Isbn,
	)
}

func (a *application) postBook(w http.ResponseWriter, r *http.Request) {
	var book models.Book
	err := json.NewDecoder(r.Body).Decode(&book)

	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	fmt.Printf("Received book: %+v\n", book)
	_, err = a.booksDB.InsertBook(book.Name, book.Author, book.Isbn)

	if err != nil {
		log.Fatal(err)
	}

	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusCreated)
	json.NewEncoder(w).Encode(book)
}
