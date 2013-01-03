/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  RTSP Client
 *  -----------
 *  Written by Eduardo Silva P. <edsiper@gmail.com>
 */

#include <stdint.h>

#ifndef RTP_H
#define RTP_H

/*
 * Struct taken from RFC 3550
 * --------------------------
 * http://www.ietf.org/rfc/rfc3550.txt
 */

struct rtp_header {
    unsigned int version:2;     /* protocol version */
    unsigned int padding:1;     /* padding flag */
    unsigned int extension:1;   /* header extension flag */
    unsigned int cc:4;          /* CSRC count */
    unsigned int marker:1;      /* marker bit */
    unsigned int pt:7;          /* payload type */
    uint16_t seq:16;            /* sequence number */
    uint32_t ts;                /* timestamp */
    uint32_t ssrc;              /* synchronization source */
    uint32_t csrc[1];           /* optional CSRC list */
};

struct rtp_stats {
    uint16_t first_seq;         /* first sequence               */
    uint16_t highest_seq;       /* highest sequence             */
    uint16_t rtp_received;      /* RTP sequence number received */
    uint32_t rtp_identifier;    /* source identifier            */
    uint32_t rtp_ts;            /* RTP timestamp                */
    uint32_t rtp_cum_lost;      /* RTP cumulative packet lost   */
    uint32_t rtp_expected_prior;/* RTP expected prior           */
    uint32_t rtp_received_prior;/* RTP received prior           */
    uint32_t jitter;            /* Jitter                       */
    struct timeval arrival_tv;  /* Last arrival timestamp       */
} rtp_st;

#define RTP_SPROP   "sprop-parameter-sets="

/* Enumeration of H.264 NAL unit types */
enum {
    NAL_TYPE_UNDEFINED = 0,
    NAL_TYPE_SINGLE_NAL_MIN	= 1,
    NAL_TYPE_SINGLE_NAL_MAX	= 23,
    NAL_TYPE_STAP_A		= 24,
    NAL_TYPE_FU_A		= 28,
};

void rtp_stats_reset();
void rtp_stats_print();
unsigned int rtp_parse(unsigned char *raw, unsigned int size);

#endif
