
Provides ability to import Evernote notes as Drupal nodes.
--------------------------------------
http://adamkempler.com/content/import-evernote-notes-drupal-devernote-module


### Installation and Setup

- Get an Evernote api key from:
  https://dev.evernote.com/doc/ (and click "GET AN API KEY").  
  Select "Full Access".  
  NOTE: this is a two step process, but simple. Once you get your api key,
  you will have to request that it be made available for production use.
  By default it is initially just for use with their sandbox site.

- Install composer.
  Composer is used to automatically install the Evernote SDK and its required dependencies.
  https://getcomposer.org/doc/00-intro.md  
  For easy global install:  
  CD into your home directory and run:  
  curl -sS https://getcomposer.org/installer | php  
  sudo mv composer.phar /usr/local/bin/composer

- Install the composer_manager module:  
  https://www.drupal.org/project/composer_manager.  
  You can configure it at: /admin/config/system/composer-manager/settings

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

- Run composer:
  cd into the files directory where the composer.json file was created when you enabled the composer_manager module. You can check by looking at  
  /admin/config/system/composer-manager/settings  
  By default it will be: public://composer  
  That would be in a "composer" directory at the path where you have specified your files to be. For example: /sites/default/files/composer  
  If you cd to that directory you should see a composer.json file.  
  Run *php composer.phar install --no-dev* on the command line. Change install to update to update dependencies.


### Usage

- Import notes on the /devernote_import page.
  Notes tagged in Evernote with the specified tag will be imported.
  Embedded images will also be imported.
  NOTE: setting the input format to Full Html on the import form works best.

- You can specify an imagecache style to apply to images that are imported
  with notes. This can be done on the /admin/config/content/devernote page.

- To reimport a note from Evernote, Delete the imported node in Drupal and
  run the import again.
  NOTE: If you change a note in Evernote that has already been imported, it will not be imported again unless you first delete it in Drupal. This is to prevent accidentally overwriting changes you might have made to the content in Drupal after importing.


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

- Haven't tested this with a business account.


Maintainers
-----------
- Adam Kemper http://adamkempler.com
