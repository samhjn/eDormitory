from django.db import models

# Create your models here.

class SwitchInfo(models.Model):
    name = models.CharField(max_length=30)
    status = models.IntegerField()

    def __unicode__(self):
        return self.name


class User(models.Model):
    userName = models.CharField(max_length=30)
    passWord = models.CharField(max_length=40)

    def __unicode__(self):
        return self.name