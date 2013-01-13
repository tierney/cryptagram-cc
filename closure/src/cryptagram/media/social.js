goog.provide('cryptagram.media.social');

goog.require('goog.Uri');
goog.require('goog.dom');

goog.require('cryptagram.container');
goog.require('cryptagram.media');

/**
 * @constructor
 */
cryptagram.media.social = function() {
  cryptagram.media.call(this);
};

goog.inherits(cryptagram.media.social, cryptagram.media);

cryptagram.media.social.prototype.supportsAutodecrypt = true;

cryptagram.media.social.prototype.logger = goog.debug.Logger.getLogger('cryptagram.media.social');

/** @inheritDoc */
cryptagram.media.social.prototype.getAlbumName = function() {
  return "untitled album";
};

/** @inheritDoc */
cryptagram.media.social.prototype.getPhotoName = function() {
  return "untitled image";
};


cryptagram.media.social.prototype.getImages = function(URL) {

  var elements = document.getElementsByTagName('img');
  var ret = new Array(); 
    for (var i = 0; i < elements.length; i++) {
      var testSrc = elements[i].src;
      if (URL == null || testSrc == URL) {
        ret.push(elements[i]);
      }
    }
  return ret;
};


cryptagram.media.social.prototype.onReady = function(callback) {
  callback();
};


cryptagram.media.social.prototype.getPhotoName = function(URL) {
  return URL;
};