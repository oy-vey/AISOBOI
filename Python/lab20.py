import requests, re
from bs4 import BeautifulSoup


def find_philosophy(url):
    MAX_HOPS = 100
    count = 0

    r = requests.get(url)
    soup = BeautifulSoup(r.text, "html.parser")

    while (soup.find(class_="firstHeading").string) != 'Philosophy':
        if count == MAX_HOPS:
            print("MAX_HOPS reached.")
            return None

        content = soup.find(id='mw-content-text')
        for t in content.find_all(class_=['navbox', 'vertical-navbox', 'toc']):
            t.replace_with("")

        paragraph = soup.select('div#mw-content-text > p')[0]  # Only DIRECT child
        for s in paragraph.find_all(
                ['span', 'small', 'sup,', 'i', 'table']):  # remove spans and smalls with language, pronounciation
            s.replace_with("")
        paragraphText = str(paragraph)
        paragraphText = re.sub(r' \(.*?\)', '', paragraphText)  # Remove leftover parenthesized text

        # For debugging:
        # print(paragraphText)

        reParagraph = BeautifulSoup(paragraphText, "html.parser")  # back into bs4 object to find links
        firstLink = reParagraph.find(href=re.compile('^/wiki/'))  # links that start with /wiki/ only

        while firstLink == None:
            # case of disambiguation: use first wiki link in list
            if '(disambiguation)' in url or '(surname)' in url:
                firstLink = content.ul.find(href=re.compile('^/wiki/'))

            else:
                paragraph = paragraph.find_next_sibling("p")

                if (paragraph is None):  # Catch-case

                    if (content.ul is not None):
                        firstLink = content.ul.find(href=re.compile('^/wiki/'))  # Disambiguation-type page
                    if (firstLink is None):  # No links available
                        print("Wikipedia not reachable.")
                        return None
                    continue

                for s in paragraph.find_all(['span', 'small', 'sup,', 'i', 'table']):
                    s.replace_with("")
                paragraphText = str(paragraph)
                paragraphText = re.sub(r' \(.*?\)', '', paragraphText)
                reParagraph = BeautifulSoup(paragraphText, "html.parser")
                firstLink = reParagraph.find(href=re.compile('^/wiki/'))

                # For debugging:
                # print(paragraphText)

        url = 'http://en.wikipedia.org' + firstLink.get('href')
        print(url)
        r = requests.get(url)  # Make new request
        soup = BeautifulSoup(r.text, "html.parser")  # Soup it up again

        count = count + 1

    print(str(count) + " hops")
    return count

find_philosophy('https://en.wikipedia.org/wiki/Python_(programming_language)')
