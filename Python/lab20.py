#-*- coding: utf-8 -*-
import requests, re
from bs4 import BeautifulSoup
from time import sleep


def find_philosophy(url, count=1, urls=dict()):
    max_attempts = 100

    sleep(0.5)
    r = requests.get(url)
    soup = BeautifulSoup(r.text, "html.parser")
    heading = soup.find(class_="firstHeading").text
    print("Attempt #: " + str(count))
    print(heading + "\n")
    if url not in urls:
        urls[url] = 1
    else:
        print("Closed loop detected")
        return None

    if heading != u"Философия":
        if count == max_attempts:
            print("Maximum attempts reached.")
            return None

        content = soup.find(id='mw-content-text')
        # Remove all information and navigation boxes
        for t in content.find_all(class_=['navbox', 'vertical-navbox', 'toc', 'infobox']):
            t.replace_with("")

        if len(soup.select('div#mw-content-text > p')) == 0:
            print "Bad Page. Exiting"
            return None
        else:
            paragraph = soup.select('div#mw-content-text > p')[0]



        # remove spans and smalls with language, pronounciation
        for s in paragraph.find_all(
                ['span', 'small', 'sup,', 'i', 'table']):
            s.replace_with("")
        paragraphText = str(paragraph)
        paragraphText = re.sub(r' \(.*?\)', '', paragraphText)  # Remove  parenthesized text

        reParagraph = BeautifulSoup(paragraphText, "html.parser")  # back into bs4 object to find links
        firstLink = reParagraph.find(href=re.compile('^/wiki/'))  # links that start with /wiki/ only

        while firstLink == None:
            # case of disambiguation: use first wiki link in list
            paragraph = paragraph.find_next_sibling("p")

            if paragraph is None:

                if content.ul is not None:
                        firstLink = content.ul.find(href=re.compile('^/wiki/'))  # Disambiguation-type page
                if firstLink is None:
                    print("Wikipedia not reachable.")
                    return None
                continue
            for s in paragraph.find_all(['span', 'small', 'sup,', 'i', 'table']):
                s.replace_with("")
            paragraphText = str(paragraph)
            paragraphText = re.sub(r' \(.*?\)', '', paragraphText)
            reParagraph = BeautifulSoup(paragraphText, "html.parser")
            firstLink = reParagraph.find(href=re.compile('^/wiki/'))


        url = 'http://ru.wikipedia.org' + firstLink.get('href')
        count += 1
        find_philosophy(url, count, urls)

find_philosophy('http://ru.wikipedia.org/wiki/Python')