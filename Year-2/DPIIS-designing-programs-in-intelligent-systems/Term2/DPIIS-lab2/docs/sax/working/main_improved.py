import xml.sax

class SongHandler(xml.sax.ContentHandler):
 
    def __init__(self):
        self.CurrentData = ''
        self.artist = ''
        self.year = ''
        self.album = ''
        
    # Call when an element starts
    def startElement(self,tag,attributes):
        # print("new tag:", tag)
        self.CurrentData=tag
        if tag == 'song':
            print('Song')
            title = attributes['title']
            #for at in attributes:
            print(attributes.getNames())
            print(f'Title: {title}')

    # Call when an elements ends
    def endElement(self,tag):
        if self.CurrentData == 'artist':
            print(f'Artist: {self.artist}')
        elif self.CurrentData == 'year':
            print(f'Year: {self.year}')
        elif self.CurrentData == 'album':
            print(f'Album: {self.album}')
        # print("data:", self.CurrentData, "|", self.artist, self.year, self.album)
        self.CurrentData = ''
        self.artist = ''
        self.year = ''
        self.album = ''
        
   # Call when a character is read
    def characters(self, content):
        # print(content)
        if self.CurrentData == 'artist':
            self.artist += content
        elif self.CurrentData == 'year':
            self.year += content
        elif self.CurrentData == 'album':
            self.album += content

if __name__ == '__main__':
    parser = xml.sax.make_parser() #creating an XMLReader
    parser.setFeature(xml.sax.handler.feature_namespaces,0) #turning off namespaces
    Handler = SongHandler()
    parser.setContentHandler(Handler) #overriding default ContextHandler
    parser.parse('songs.xml')