import argparse
import requests

def download(url, filename):
    if filename is None:
        filename = url.split('/')[-1]
    with requests.get(url, stream=True) as r:
        r.raise_for_status()
        with open(filename, 'wb') as f:
            for chunk in r.iter_content(chunk_size=8192):
                f.write(chunk)

parser = argparse.ArgumentParser()
parser.add_argument('url', help='URL to download')
parser.add_argument('filename', nargs='?', help='Filename to save as',default=None)
args = parser.parse_args()
print(args)
download(args.url, args.filename)