<?php
/**
 * @file
 * Provide a settings form for the devernote module.
 */

/**
 * Provide a settings form for the module.
 */
function devernote_settings_form() {

  $keys = devernote_load_keys();
  if ($keys) {
    $secret = ($keys['secret_key'] == '0') ? '' : $keys['secret_key'];
    $consumer = ($keys['consumer_key'] == '0') ? '' : $keys['consumer_key'];
  } else {
    $secret = '';
    $consumer = '';
  }

  $form = array();
  /*
  $form['devernote_delete_auth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete authorization'),
    '#default_value' => 0,
    '#description' => t('Delete the current Evernote authorization. This will force a reauthorization to import notes.'),
  );
  */
  $form['devernote_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer Key'),
    '#default_value' => $consumer,
    '#description' => t('The Consumer Key provided by Evernote when signing up for an API Key.'),
  );

  $form['devernote_secret_key'] = array(
    '#type' => 'password',
    '#title' => t('Secret Key'),
    '#default_value' => $secret,
    '#description' => t('The Secret Key provided by Evernote when signing up for an API Key.'),
  );

  $form['devernote_nodestatus'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#default_value' => variable_get('devernote_nodestatus', 0),
    '#description' => t('Set the default status of imported notes. This can be overridden when importing a note.'),
  );

  $form['devernote_nodepromoted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Promoted to front page'),
    '#default_value' => variable_get('devernote_nodepromoted', 1),
    '#description' => t('Set the default value for imported notes. This can be overridden when importing a note.'),
  );

  $form['devernote_nodecomments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow comments'),
    '#default_value' => variable_get('devernote_nodecomments', 1),
    '#description' => t('Set the default value for imported notes. This can be overridden when importing a note.'),
  );

  global $user;
  $formats = filter_formats($user);
  $default_format = filter_default_format($user);
  $options = array();
  foreach ($formats as $format) {
    $options[$format->format] = $format->name;
  }
  if (count($options)) {
    $form['devernote_inputformat'] = array(
      '#type' => 'select',
      '#title' => t('Input Format'),
      '#options' => $options,
      '#default_value' => variable_get('devernote_inputformat', $default_format),
      '#description' => t('Select an input format for the imported note.'),
    );
  }

  $options = array();
  // Probably safe to assume it would always be enabled?
  if (module_exists('image')) {
    $styles = image_styles();
    if (count($styles)) {
      foreach ($styles as $key => $style) {
        $options[$key] = $style['label'];
      }
    }
  }

  $none = array('none' => t('None'));
  $options = $none + $options;
  $form['devernote_imagestyle'] = array(
    '#type' => 'select',
    '#title' => t('Image Style'),
    '#options' => $options,
    '#default_value' => variable_get('devernote_imagestyle', 'none'),
    '#description' => t('An image style to apply to imported images.'),
  );

  $isloaded = extension_loaded('libxml');
  if ($isloaded) {
    $form['conversions'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced HTML Conversions:'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#group' => 'html_conversions',
      '#attributes' => array(
        'class' => array('node-form-options'),
      ),
    );
    $form['conversions']['devernote_div2p'] = array(
        '#type' => 'checkbox',
        '#title' => t('Convert divs to p tags'),
        '#default_value' => variable_get('devernote_div2p', 0),
        '#description' => t('Check this to convert divs to p tags. This can be overridden when importing a note.'),
    );
    $form['conversions']['convertheadings_info'] = array(
      '#markup' => '<strong>Font size to heading tag conversions</strong><br />
                    When you set different font sizes in Evernote, it uses the font-size attribute to style the text.
                    If you prefer to have your html rendered using html h tags instead, you can use the following text area to specify conversions.<br />
                    Enter font sizes followed by a comma with the corresponding html h tag you want it converted to.
                    One per line. For example:<br />
                    11, h5<br />
                    12, h5<br />
                    13, h4<br />
                    With the above settings, when the note gets imported any text wrapped with a &lt;div style="font-size: 11px;"&gt; would get wrapped in an h5 tag instead. <br />
                    These settings can be overridden when importing a note.<br />
                    NOTE: these settings will be ignored if the input format is set to plain text when importing.',
    );
    $form['conversions']['devernote_convertheadings'] = array(
        '#type' => 'textarea',
        '#title' => t('Heading Conversions'),
        '#default_value' => variable_get('devernote_convertheadings', ''),
        '#description' => t('Convert font sizes to html h tags.'),
    );
  }

  //$form['#submit'][] = 'delete_auth_handler';
  $form['#submit'][] = 'save_keys_handler';

  return system_settings_form($form);
}


function save_keys_handler($form, &$form_state) {

  global $user;

  $secret = $form_state['values']['devernote_secret_key'];
  if (module_exists('aes')) {
    $secret = aes_encrypt($secret);
  }
  elseif (module_exists('encrypt')) {
    $secret = encrypt($secret);
  }
  $consumer = $form_state['values']['devernote_consumer_key'];

  db_merge('devernote_user')
  ->key(array('uid' => $user->uid))
  ->fields(array(
      'secret_key' => $secret,
      'consumer_key' => $consumer,
  ))
  ->execute();

  global $user;
}


function delete_auth_handler($form, &$form_state) {

  global $user;

  $delete = $form_state['values']['devernote_delete_auth'];
  if ($delete === 1) {

    db_update('devernote_user')
    ->fields( array (
      'oauth_token' => 0,
      'expires' => 0,
    ))
    ->condition('uid' , $user->uid)
    ->execute();
  }
}


