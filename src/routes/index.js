var express = require('express');
var router = express.Router();
const indexController = require('../controllers/indexController.js');

/* GET home page. */
router.get('/', indexController.index);
router.get('/on', indexController.on);
router.get('/off', indexController.off);
router.get('/listen', indexController.listen);

module.exports = router;
