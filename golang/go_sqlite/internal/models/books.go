package models

import (
	"database/sql"
	"errors"
	"log"
)

type Book struct {
	id     int
	Name   string `json:"name"`
	Author string `json:"author"`
	Isbn   int    `json:"isbn"`
}

// Define a Books type which wraps a sql.DB connection pool.
type Books struct {
	DB *sql.DB
}

func (b *Books) StartBooksDB(withStartingData bool) {

	statement, err := b.DB.Prepare("CREATE TABLE IF NOT EXISTS books (id INTEGER PRIMARY KEY, isbn INTEGER, author VARCHAR(64), name VARCHAR(64) NULL)")

	if err != nil {
		log.Println("Error in creating table")
	} else {
		log.Println("Successfully created table books!")
	}
	statement.Exec()

	if withStartingData {
		b.InsertBook("A Tale of Two Cities", "Charles Dickens", 140430547)
		log.Println("Database successfully initialized with starting data.")
	}
}

func (b *Books) InsertBook(name string, author string, isbn int) (int, error) {

	statement, _ := b.DB.Prepare("INSERT INTO books (name, author, isbn) VALUES (?, ?, ?)")

	res, err := statement.Exec(name, author, isbn)

	if err != nil {
		return 1, err
	}

	id, err := res.LastInsertId()
	if err != nil {
		return 0, err
	}

	log.Println("Inserted the book into database!")
	return int(id), nil

}

func (b *Books) SelectBook(id int) (Book, error) {
	row := b.DB.QueryRow("SELECT name, author, isbn FROM books where id=?", id)
	var tempBook Book
	err := row.Scan(&tempBook.Name, &tempBook.Author, &tempBook.Isbn)
	// log.Printf("ID:%d, Book:%s, Author:%s\n", tempBook.id,
	// 	tempBook.name, tempBook.author)
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return Book{}, ErrNoRecord
		} else {
			return Book{}, err
		}
	}

	// If everything went OK, then return the filled Snippet struct.
	return tempBook, nil
}

func (b *Books) updateBook(id int) {
	statement, _ := b.DB.Prepare("update books set name=? where id=?")
	statement.Exec("A Tale of Three Cities", id)
	log.Println("Successfully updated the book in database!")
}

func (b *Books) deleteBook(id int) {
	statement, _ := b.DB.Prepare("delete from books where id=?")
	statement.Exec(id)
	log.Println("Successfully deleted the book in database!")
}
