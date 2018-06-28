library(ggplot2)
library(here)

args <- commandArgs(trailingOnly = TRUE)

if(length(args) < 1) {
    print("Please inform the data file!")
    quit()
}

inputFile <- paste0(here(), "/", args[1])
data <- read.csv(inputFile, header = TRUE)

plot <- ggplot(data, aes(x = edges, y = time)) + 
    geom_line() +
    geom_point(size = 2) +
    scale_x_continuous(breaks = seq(0, 100000, 10000)) +
    #scale_y_continuous(breaks = seq(0, 1, 0.1)) +
    xlab("Número de arestas") +
    ylab("Tempo (ms)") +
    theme_bw()

ggsave("plot.pdf", plot, device = pdf(), width = 6, height = 4, unit = "in")