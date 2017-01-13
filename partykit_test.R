library(partykit)
library(rpart)
library(party)
library("RWeka")

## ForestFactory generated R script

source("partykit.R")


## set up party object
data("iris")
dat = iris
resp = iris$Species

dat <-read.csv("easy.csv", sep = ";", na.strings=c("", "NA", "NULL"), dec = ",", header=TRUE)
dat <- dat[,1:3]
resp <- dat$Y

tree <- party(node,
              data = dat,
              fitted = data.frame("(fitted)" = fitted_node(node, data = dat),
                                  "(response)" = resp,
                                  check.names = FALSE),
                                  terms = terms(Species ~ ., data = dat),
              )

t2 <- as.constparty(tree)
plot(t2)

## number of kids in root node
length(tree)
## depth of tree
depth(tree)
## number of terminal nodes
width(tree)
## number of terminal nodes
plot(tree)

notMy.tree = rpart(Species ~ ., data=dat)
plot(as.constparty(notMy.tree))


j48.tree <- as.party(J48(Species ~ ., data = dat))
plot(as.constparty(j48.tree))



par(mfrow=c(2,1))
plot(tree)
summary(notMy.tree)
summary(tree)



