
Provides ability to import Evernote notes as Drupal nodes.
--------------------------------------
http://adamkempler.com


### Installation and Setup
  
- Get an Evernote api key from:
  https://dev.evernote.com/doc/ (and click "GET AN API KEY").
  Select "Full Acess"
  NOTE: this is a two step process. Once you get your api key, 
  you will have to request that it be made available for production use.
  By default it is initially just for use with their sandbox site.
  
- Install composer:
  https://getcomposer.org/doc/00-intro.md
  For easy global insall:
  CD into your home directory and run:
  curl -sS https://getcomposer.org/installer | php
  sudo mv composer.phar /usr/local/bin/composer
  
- Install the composer_manager module:
  https://www.drupal.org/project/composer_manager
  
- Install the aes or encrypt module:
  https://www.drupal.org/project/aes
  https://www.drupal.org/project/encrypt
  Not required but recommended. 
  If one is installed, the auth key will be encrypted.
  
- Install the devernote module.
  Configure it at: /admin/config/content/devernote
  Specify permissions for which roles can administer and import notes.
  Tag notes in evernote with "drupalimport".
  Import notes at: /devernote_import
  

### Usage

- Import notes on the /devernote_import page.
  Notes tagged in Evernote with the specified tag will be imported. 
  Embedded images will also be imported.
  NOTE: setting the input format to Full Html works best.
  
- You can specify an imagecache style to apply to images that are imported 
  with notes. This can be done on the /admin/config/content/devernote page.
  
- To reimport a note from Evernote, just delete the node in Drupal and 
  run the import again.
  

### Limitations

- Fields: Currently it only uses the title and body fields of nodes.
  A longer term, more flexible solution would be to let the user 
  select the fields for the specified content type that the note will be 
  imported into.
  
- Importing files: Currently it will only import embedded images. 
  Additionally it will place them as inline images (though you can specify 
  an imagecache image style for sizing). At some point I'll add the ability 
  to save images and other attached files to a file field.
  
- Doesn't work with Private files yet. 
  This will be implemented in the next release.


Maintainers
-----------
- Adam Kemper http://adamkempler.com
