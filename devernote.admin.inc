<?php
/**
 * @file
 * Provide a settings form for the devernote module.
 */

/**
 * Provide a settings form for the module.
 */
function devernote_settings_form() {
  $form = array();

  $form['devernote_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer Key'),
    '#default_value' => variable_get('devernote_consumer_key', ''),
    '#description' => t('The Consumer Key provided by Evernote when signing up for an API Key.'),
  );

  $form['devernote_secret_key'] = array(
    '#type' => 'password',
    '#title' => t('Secret Key'),
    '#default_value' => variable_get('devernote_secret_key', ''),
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

  return system_settings_form($form);
}
