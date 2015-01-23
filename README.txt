
Provides ability to import Evernote notes as Drupal nodes.
--------------------------------------
http://adamkempler.com


### Installation and Setup

- Install the composer_manager module:
  https://www.drupal.org/project/composer_manager
  
- Install the aes or encrypt module:
  https://www.drupal.org/project/aes
  Not required but if it's installed, 
  the auth key will be encrypted.
  
- Get an Evernote api key from:
  https://dev.evernote.com/doc/ (and click "GET AN API KEY").
  Select "Full Acess"
  NOTE: this is a two step process. Once you get your api key, 
  you will have to request that it be made available for production use.
  By default it is initially just for use with their sandbox site.

- Install the devernote module.
  Configure it at: /admin/config/content/devernote
  Specify permissions for which roles can administer and import notes.
  Tag notes in evernote with "drupalimport".
  Import notes at: /devernote_import
  

### Usage

- Import notes on the /devernote_import page.
  Notes tagged in Evernote with the specified tag will be imported.
  
- To reimport a note from Evernote, just delete the node in Drupal and 
  run the import again.
  

### Limitations

- Fields: Currently is only uses the title and body fields of nodes.
  A more flexible solution would be to let the user select the fields for 
  the specified content type that the note will be imported into.
  
- Importing files: Currently it will only import embedded images. 
  Additionally it will place them as inline images (though you can specify 
  an imagecache image style for sizing). At some point I'll add the ability 
  to save images and other attached files to a file field.
  
- Doesn't work with Private files yet. 
  This will be implemented in the next release.


Maintainers
-----------
- Adam Kemper http://adamkempler.com
