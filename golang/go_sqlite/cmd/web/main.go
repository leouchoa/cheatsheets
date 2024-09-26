package main

import (
	"database/sql"
	"go_sqlite/internal/models"
	"log"
	"net/http"

	_ "github.com/mattn/go-sqlite3"
)

type application struct {
	// logger *slog.Logger
	booksDB *models.Books
}

func main() {

	db, err := sql.Open("sqlite3", "books.db")
	if err != nil {
		log.Println(err)
	}

	app := &application{
		booksDB: &models.Books{DB: db},
	}

	app.booksDB.StartBooksDB(true)

	mux := http.NewServeMux()
	mux.HandleFunc("/{$}", app.home)
	mux.HandleFunc("GET /user/getBook/{id}", app.getBook)
	mux.HandleFunc("POST /user/postBook", app.postBook)

	log.Print("Listening on port 8080")

	err = http.ListenAndServe(":8080", mux)
	log.Fatal(err)

}
